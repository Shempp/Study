#pragma once

#include <cstdint>
#include <vector>
#include <memory>

struct Range {
    Range(uintptr_t ptr, uintptr_t size) noexcept
        : m_startAddress(ptr)
        , m_size(size)
    { }
    
    bool operator<(const Range& other) const
    {
        return (m_startAddress < other.m_startAddress || 
                m_startAddress + m_size < other.m_startAddress + other.m_size);
    }
    
    uintptr_t m_startAddress;
    uintptr_t m_size;
};

namespace Intervals {
    template <typename IntervalType, typename ValueType>
    class IntervalTree;
}

class RangeArray
{
public:
    RangeArray();
    explicit RangeArray(const std::vector<Range>& ranges);
    ~RangeArray();

    RangeArray(const RangeArray&) = delete;
    RangeArray(RangeArray&&) = default;

    RangeArray& operator=(const RangeArray&) = delete;
    RangeArray& operator=(RangeArray&&) = default;

    bool Insert(const Range& range);
    bool Remove(const Range& range);
    void Remove(uintptr_t addr);
    std::vector<Range> FindContaining(uintptr_t addr) const;
    void Clear();
    bool IsEmpty() const;
    bool Contains(const Range& range) const;
    std::vector<Range> Ranges() const;

private:
    std::unique_ptr<Intervals::IntervalTree<uintptr_t, Range>> m_intervalTree;
};