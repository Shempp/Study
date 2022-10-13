#pragma once

#pragma once

#include <vector>
#include <cassert>
#include <mutex>

template<typename T>
class CRenderQueueMutex
{
public:
	explicit CRenderQueueMutex(size_t size)
		// Queue should have one dummy element
		: arr_(size + 1)
		, capacity_(size + 1)
		, writeIdx_(0)
		, readIdx_(0)
	{
		assert(size > 0);
	}
	~CRenderQueueMutex() = default;

	CRenderQueueMutex(const CRenderQueueMutex&) = delete;
	CRenderQueueMutex& operator=(const CRenderQueueMutex&) = delete;

	CRenderQueueMutex(CRenderQueueMutex&&) noexcept = delete;
	CRenderQueueMutex& operator=(CRenderQueueMutex&&) noexcept = delete;

	bool AddCommand(const T& e) {
		std::lock_guard<std::mutex> lg(m);
		const auto newWriteIdx = (writeIdx_ + 1) % capacity_;

		// Check if queue is full
		if (newWriteIdx == readIdx_) {
			return false;
		}

		arr_[writeIdx_] = e;
		writeIdx_ = newWriteIdx;

		return true;
	}

	bool PopCommand(T& e) {
		std::lock_guard<std::mutex> lg(m);

		// Check if queue is empty
		if (readIdx_ == writeIdx_) {
			return false;
		}

		e = arr_[readIdx_];
		const auto newReadIdx = (readIdx_ + 1) % capacity_;
		readIdx_ = newReadIdx;

		return true;
	}

	void Flush() {
		for (auto i = 0ULL; ; ++i) {
			{
				std::lock_guard<std::mutex> lg(m);
				if (writeIdx_ == readIdx_) {
					break;
				}
			}

			if (i % 100 == 0) {
				std::this_thread::yield();
			}
		}
	}

	void Reset() {
		Flush();

		std::lock_guard<std::mutex> lg(m);
		writeIdx_ = 0;
		readIdx_ = 0;
	}

private:
	std::vector<T> arr_;
	const size_t capacity_;
	std::mutex m;
	size_t writeIdx_;
	size_t readIdx_;
};
