#include "RangeArray.h"

#include "IntervalTree/intervaltree.hpp"

using namespace Intervals;

RangeArray::RangeArray()
    : m_intervalTree(std::make_unique<IntervalTree<uintptr_t, Range>>())
{
}

RangeArray::RangeArray(const std::vector<Range>& ranges)
    : m_intervalTree(std::make_unique<IntervalTree<uintptr_t, Range>>())
{
    for (const auto& range : ranges) {
        m_intervalTree->insert({ range.m_startAddress, range.m_startAddress + range.m_size, range });
    }
}

RangeArray::~RangeArray()
{
}

bool RangeArray::Insert(const Range& range)
{
    return m_intervalTree->insert({ range.m_startAddress, range.m_startAddress + range.m_size, range });
}

bool RangeArray::Remove(const Range& range)
{
    return m_intervalTree->remove({ range.m_startAddress, range.m_startAddress + range.m_size, range });
}

void RangeArray::Remove(uintptr_t addr)
{
    auto rangesToRemove = m_intervalTree->findIntervalsContainPoint(addr);
    for (const auto& range : rangesToRemove) {
        m_intervalTree->remove(range);
    }
}

std::vector<Range> RangeArray::FindContaining(uintptr_t addr) const
{
    std::vector<Range> result;
    auto rangesContain = m_intervalTree->findIntervalsContainPoint(addr);
    result.reserve(rangesContain.size());
    for (const auto& range : rangesContain) {
        result.emplace_back(range.value);
    }
    return result;
}

void RangeArray::Clear()
{
    m_intervalTree->clear();
}

bool RangeArray::IsEmpty() const
{
    return m_intervalTree->isEmpty();
}

bool RangeArray::Contains(const Range& range) const
{
    return m_intervalTree->contains({ range.m_startAddress, range.m_startAddress + range.m_size, range });
}

std::vector<Range> RangeArray::Ranges() const
{
    std::vector<Range> result;
    auto intervals = m_intervalTree->intervals();
    result.reserve(intervals.size());
    for (const auto& interval : intervals) {
        result.emplace_back(interval.value);
    }
    return result;
}