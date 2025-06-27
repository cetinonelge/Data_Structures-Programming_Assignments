#include <iostream>
#include <stdexcept>
#include <cstdlib>

struct MemoryTableEntry
{
    void* address;
    size_t count;
    bool isArray;
    const char* fileName;
    size_t lineNo;
};

constexpr MemoryTableEntry EMPTY_TABLE_ENTRY = { nullptr, 0, false, nullptr, 0 };

#define LEAK_DETECTOR_TABLE_SIZE 10000

class LeakDetector
{
private:
    MemoryTableEntry m_table[LEAK_DETECTOR_TABLE_SIZE];

public:
    LeakDetector()
    {
        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            m_table[i] = EMPTY_TABLE_ENTRY;
        }
    }

    ~LeakDetector()
    {
        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            if (m_table[i].address == nullptr) continue;

            std::cout << "[Leak Detector] Address " << m_table[i].address << " is not deleted by \"operator new"
                << (m_table[i].isArray ? "[]\"" : "\"") << ".\n";
            std::cout << "[Leak Detector] \tAllocation happened at \"" << m_table[i].fileName << ":" << m_table[i].lineNo
                << "\"\n";
        }
    }

    void record_allocation(void* address, size_t count, bool isArray, const char* fileName, size_t lineNo)
    {
        if (address == nullptr) return;

        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            if (m_table[i].address != nullptr) continue;

            m_table[i] = { address, count, isArray, fileName, lineNo };
            return;
        }

        std::cout << "\n[Leak Detector] Leak Detector Table is full.\n" << std::endl;
        exit(-1);
    }

    void record_deletion(void* address, size_t count, bool isArray)
    {
        if (address == nullptr) return;

        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            if (m_table[i].address != address) continue;

            if (m_table[i].count != count) {
                std::cout << "[Leak Detector] Address " << address << " is deleted with a wrong size." << std::endl;
                std::cout << "[Leak Detector] \tAllocation happened at \"" << m_table[i].fileName << ":" << m_table[i].lineNo
                    << "\"\n";
                exit(-1);
            }

            if (m_table[i].isArray != isArray) {
                std::cout << "[Leak Detector] Address " << address << " is deleted with a wrong operator." << std::endl;
                std::cout << "[Leak Detector] \tAllocation happened at \"" << m_table[i].fileName << ":" << m_table[i].lineNo
                    << "\"\n";
                exit(-1);
            }

            m_table[i] = EMPTY_TABLE_ENTRY;
            return;
        }

        std::cout << "[Leak Detector] Address " << address << " is deleted without allocation." << std::endl;
        exit(-1);
    }
};

static LeakDetector leakDetector;

void* operator new(size_t count, const char* fileName, size_t lineNo)
{
    void* ptr = std::malloc(count);
    leakDetector.record_allocation(ptr, count, false, fileName, lineNo);
    return ptr;
}

void* operator new[](size_t count, const char* fileName, size_t lineNo)
{
    void* ptr = std::malloc(count);
    leakDetector.record_allocation(ptr, count, true, fileName, lineNo);
    return ptr;
}

void* operator new(size_t count)
{
    return operator new(count, "unknown", 0);
}

void* operator new[](size_t count)
{
    return operator new[](count, "unknown", 0);
}

void operator delete(void* ptr, size_t count)
{
    leakDetector.record_deletion(ptr, count, false);
    std::free(ptr);
}

void operator delete[](void* ptr, size_t count)
{
    leakDetector.record_deletion(ptr, count, true);
    std::free(ptr);
}

void operator delete(void* ptr, size_t count, const char* fileName, size_t lineNo)
{
    operator delete(ptr, count);
}

void operator delete[](void* ptr, size_t count, const char* fileName, size_t lineNo)
{
    operator delete[](ptr, count);
}
