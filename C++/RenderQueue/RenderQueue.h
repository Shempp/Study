#pragma once

#include <vector>
#include <atomic>
#include <cassert>

// SPSC lock-free wait-free (except Flush and Reset methods) bounded queue (based on ring buffer)
template<typename T>
class CRenderQueue
{
public:
	explicit CRenderQueue(size_t size)
		// Queue should have one dummy element
		: arr_(size + 1)
		, capacity_(size + 1)
		, writeIdx_(0)
		, readIdx_(0)
	{
		assert(size > 0);
	}
	~CRenderQueue() = default;

	CRenderQueue(const CRenderQueue&) = delete;
	CRenderQueue& operator=(const CRenderQueue&) = delete;

	CRenderQueue(CRenderQueue&&) noexcept = delete;
	CRenderQueue& operator=(CRenderQueue&&) noexcept = delete;

	bool AddCommand(const T& val) {
		const auto writeIdx = writeIdx_.load(std::memory_order_relaxed);
		const auto newWriteIdx = (writeIdx + 1) % capacity_;

		// Check if queue is full
		if (newWriteIdx == readIdx_.load(std::memory_order_acquire)) {
			return false;
		}

		arr_[writeIdx] = val;
		writeIdx_.store(newWriteIdx, std::memory_order_release);

		return true;
	}

	bool PopCommand(T& val) {
		const auto readIdx = readIdx_.load(std::memory_order_relaxed);

		// Check if queue is empty
		if (readIdx == writeIdx_.load(std::memory_order_acquire)) {
			return false;
		}

		val = arr_[readIdx_];
		const auto newReadIdx = (readIdx + 1) % capacity_;
		readIdx_.store(newReadIdx, std::memory_order_release);

		return true;
	}

	// Can be used only in producer thread
	// Warning: there will be a infinity lock if the consumer's thread has stopped before this method called 
	void Flush() {
		const auto writeIdx = writeIdx_.load(std::memory_order_relaxed);
		for (auto i = 0ULL; ; ++i) {
			if (writeIdx == readIdx_.load(std::memory_order_acquire)) {
				break;
			}
			if (i % 100 == 0) {
				std::this_thread::yield();
			}
		}
	}

	// Can be used only in producer thread
	// Warning: there will be a infinity lock if the consumer's thread has stopped before this method called 
	void Reset() {
		Flush();
		writeIdx_.store(0, std::memory_order_relaxed);
		readIdx_.store(0, std::memory_order_release);
	}
private:
	std::vector<T> arr_;
	const size_t capacity_;
	std::atomic<size_t> writeIdx_;
	std::atomic<size_t> readIdx_;
};
