#pragma once
#include <vector>
#include <cstring>

namespace sjtu {
class CrossArray {
private:
    int maxLines;
    std::vector<int*> arrays; // pointers to each 1D array
    std::vector<int> lengths; // length of each array
public:
    explicit CrossArray(int lines) : maxLines(lines), arrays(lines, nullptr), lengths(lines, 0) {}

    // copy constructor – deep copy
    CrossArray(const CrossArray &o) : maxLines(o.maxLines), arrays(o.maxLines, nullptr), lengths(o.lengths) {
        for (int i = 0; i < maxLines; ++i) {
            if (o.arrays[i]) {
                int sz = o.lengths[i];
                arrays[i] = new int[sz];
                std::memcpy(arrays[i], o.arrays[i], sz * sizeof(int));
            }
        }
    }

    // Insert a new array; returns false if no space left
    bool InsertArrays(const int *Input, int size) {
        // find first nullptr slot
        int idx = -1;
        for (int i = 0; i < maxLines; ++i) {
            if (arrays[i] == nullptr) { idx = i; break; }
        }
        if (idx == -1) return false; // no free slot
        arrays[idx] = new int[size];
        std::memcpy(arrays[idx], Input, size * sizeof(int));
        lengths[idx] = size;
        return true;
    }

    // Append to existing array at line
    void AppendArrays(const int *Input, int Line, int size) {
        // assume Line is valid and already has an array
        int oldSize = lengths[Line];
        int newSize = oldSize + size;
        int *newArr = new int[newSize];
        if (oldSize > 0) {
            std::memcpy(newArr, arrays[Line], oldSize * sizeof(int));
            delete[] arrays[Line];
        }
        std::memcpy(newArr + oldSize, Input, size * sizeof(int));
        arrays[Line] = newArr;
        lengths[Line] = newSize;
    }

    // Return reference to the larger (by total element count) CrossArray
    CrossArray &WhichGreater(CrossArray &o) {
        long long totalThis = 0, totalOther = 0;
        for (int len : lengths) totalThis += len;
        for (int len : o.lengths) totalOther += len;
        return (totalThis >= totalOther) ? *this : o;
    }

    // Check if two objects share the same underlying storage (i.e., are the same object)
    bool IsSame(const CrossArray &o) {
        return this == &o;
    }

    // Double the capacity (maxLines)
    void DoubleCrossLength() {
        int old = maxLines;
        maxLines *= 2;
        arrays.resize(maxLines, nullptr);
        lengths.resize(maxLines, 0);
    }

    // Get pointer to array i (may be nullptr)
    const int *AtArray(int i) const {
        return arrays[i];
    }

    // Access element reference
    int &At(int i, int j) {
        return arrays[i][j];
    }

    // Destructor
    ~CrossArray() {
        for (int *ptr : arrays) {
            delete[] ptr;
        }
    }
};
} // namespace sjtu
