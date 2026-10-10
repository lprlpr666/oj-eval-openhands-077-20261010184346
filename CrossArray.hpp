#pragma once
#include <cstring>

namespace sjtu {
class CrossArray {
private:
    int maxLines;          // maximum number of lines (arrays)
    int **arrays;          // pointer to array of int* for each line
    int *lengths;          // length of each line
public:
    explicit CrossArray(int lines) : maxLines(lines) {
        arrays = new int*[maxLines];
        lengths = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            arrays[i] = nullptr;
            lengths[i] = 0;
        }
    }

    // Deep copy constructor
    CrossArray(const CrossArray &o) : maxLines(o.maxLines) {
        arrays = new int*[maxLines];
        lengths = new int[maxLines];
        for (int i = 0; i < maxLines; ++i) {
            lengths[i] = o.lengths[i];
            if (o.arrays[i]) {
                arrays[i] = new int[lengths[i]];
                std::memcpy(arrays[i], o.arrays[i], lengths[i] * sizeof(int));
            } else {
                arrays[i] = nullptr;
            }
        }
    }

    // Insert a new array; returns false if capacity exceeded
    bool InsertArrays(const int *Input, int size) {
        // find first nullptr slot
        for (int i = 0; i < maxLines; ++i) {
            if (arrays[i] == nullptr) {
                arrays[i] = new int[size];
                std::memcpy(arrays[i], Input, size * sizeof(int));
                lengths[i] = size;
                return true;
            }
        }
        return false; // no free slot
    }

    // Append to existing array at given line (Line is valid and already inserted)
    void AppendArrays(const int *Input, int Line, int size) {
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

    // Return reference to the CrossArray with greater total element count (or this if equal)
    CrossArray &WhichGreater(CrossArray &o) {
        long long totalThis = 0, totalOther = 0;
        for (int i = 0; i < maxLines; ++i) totalThis += lengths[i];
        for (int i = 0; i < o.maxLines; ++i) totalOther += o.lengths[i];
        return (totalThis >= totalOther) ? *this : o;
    }

    // Check if two objects share the same underlying storage (i.e., are the same object)
    bool IsSame(const CrossArray &o) {
        return this == &o;
    }

    // Double the capacity (maxLines) while preserving existing data
    void DoubleCrossLength() {
        int newMax = maxLines * 2;
        int **newArrays = new int*[newMax];
        int *newLengths = new int[newMax];
        for (int i = 0; i < maxLines; ++i) {
            newArrays[i] = arrays[i];
            newLengths[i] = lengths[i];
        }
        for (int i = maxLines; i < newMax; ++i) {
            newArrays[i] = nullptr;
            newLengths[i] = 0;
        }
        delete[] arrays;
        delete[] lengths;
        arrays = newArrays;
        lengths = newLengths;
        maxLines = newMax;
    }

    // Get pointer to array i (may be nullptr)
    const int *AtArray(int i) {
        return arrays[i];
    }

    // Access element reference
    int &At(int i, int j) {
        return arrays[i][j];
    }

    // Destructor
    ~CrossArray() {
        for (int i = 0; i < maxLines; ++i) {
            delete[] arrays[i];
        }
        delete[] arrays;
        delete[] lengths;
    }
};
} // namespace sjtu
