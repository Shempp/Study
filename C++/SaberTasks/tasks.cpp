#include "tasks.h"

#include <limits>
#include <iostream>
#include <vector>
#include <unordered_map>

#include <cassert>

using namespace tasks;

// First task
void tasks::PrintBinary(long long number) {
    for (auto i = std::numeric_limits<long long>::digits; i >= 0; --i) {
        std::cout << ((number >> i) & 1);
    }
    std::cout << std::endl;
}

// Second task
void tasks::RemoveDups(char* str) {
    if (!str) {
        return;
    }

    char previousCh = {};
    auto writePos = str;
    auto readPos = str;
    for (; *readPos != '\0'; ++readPos) {
        auto ch = *readPos;
        if (previousCh != ch) {
            *writePos = ch;
            ++writePos;
        }

        previousCh = ch;
    }

    std::memset(writePos, '\0', readPos - writePos);
}

// Third task
namespace {
    enum class ListNodeIndex {
        INVALID_ID = -1
    };
}

List::List() 
    : head(nullptr),
    tail(nullptr),
    count(0)
{ }

List::~List() {
    while (head) {
        auto del = head;
        head = head->next;
        delete del;
    }
}

bool List::Empty() const {
    return count == 0;
}

int List::Size() const {
    return count;
}

std::string List::Front() const {
    assert(head);
    return head->data;
}

void List::PushFront(std::string val) {
    auto node = new ListNode();
    node->next = head;
    node->data = val;

    if (head) {
        head->prev = node;
    }
    head = node;
    if (!tail) {
        tail = node;
    }

    ++count;
}

void List::PopFront() {
    assert(head);

    auto node = head;

    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    else {
        head->prev = nullptr;
    }

    delete node;

    --count;
}

std::string List::Back() const {
    assert(tail);
    return tail->data;
}

void List::PushBack(std::string val) {
    auto node = new ListNode();
    node->prev = tail;
    node->data = val;

    if (tail) {
        tail->next = node;
    }
    tail = node;
    if (!head) {
        head = node;
    }

    ++count;
}

void List::PopBack() {
    assert(tail);

    auto node = tail;

    tail = tail->prev;
    if (!tail) {
        head = nullptr;
    }
    else {
        tail->next = nullptr;
    }

    delete node;

    --count;
}

void List::SetRandomLink(int pos, int randPos) {
    auto node = head;
    while (pos) {
        assert(node);
        node = node->next;
        pos--;
    }

    auto randNode = head;
    while (randPos) {
        assert(randNode);
        randNode = randNode->next;
        randPos--;
    }

    node->rand = randNode;
}

void List::Serialize(FILE* file) {
    if (!file) {
        return;
    }

    if (Empty()) {
        return;
    }
     
    std::unordered_map<ListNode*, int> indexes(count);

    // Count
    std::fwrite(&count, sizeof(count), 1, file);

    // Data of nodes
    int i = 0;
    for (auto node = head; node != nullptr; node = node->next) {
        // Size
        size_t size = node->data.size();
        std::fwrite(&size, sizeof(size), 1, file);
        // Data
        std::fwrite(node->data.c_str(), sizeof(char), size, file);

        // Fill random indexes
        indexes.emplace(node, i);
        ++i;
    }

    // Fill random links
    for (auto node = head; node != nullptr; node = node->next) {
        if (node->rand) {
            auto index = indexes[node->rand];
            std::fwrite(&index, sizeof(index), 1, file);
        }
        else {
            int noRandID = static_cast<int>(ListNodeIndex::INVALID_ID);
            std::fwrite(&noRandID, sizeof(noRandID), 1, file);
        }
    }
}

void List::Deserialize(FILE* file) {
    if (!file) {
        return;
    }

    // Count
    int countFromFile = 0;
    std::fread(&countFromFile, sizeof(countFromFile), 1, file);

    std::unordered_map<int, ListNode*> indexes(countFromFile);

    // Data of nodes
    for (auto i = 0; i < countFromFile; ++i) {
        // Size
        size_t size = 0;
        std::fread(&size, sizeof(size), 1, file);
        // Data
        std::string data(size, '\0');
        std::fread(&data[0], sizeof(char), size, file);

        PushBack(std::move(data));

        // Fill random indexes
        indexes.emplace(i, tail);
    }

    // Restore random links
    for (auto node = head; node != nullptr; node = node->next) {
        // Random link index
        auto index = static_cast<int>(ListNodeIndex::INVALID_ID);
        std::fread(&index, sizeof(count), 1, file);

        if (index != static_cast<int>(ListNodeIndex::INVALID_ID)) {
            node->rand = indexes[index];
        }
    }
}