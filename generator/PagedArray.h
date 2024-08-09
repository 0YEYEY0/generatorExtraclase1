#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <fstream>
#include <vector>

class PagedArray {
public:
    PagedArray(const std::string& filePath, size_t size);
    ~PagedArray();

    int& operator[](size_t index);
    size_t getNumPageFaults() const;
    size_t getNumPageHits() const;

private:
    void loadPage(size_t pageIndex);
    void unloadPage(size_t pageIndex);
    size_t pageSize;
    size_t numPages;
    size_t numElements;
    std::string filePath;
    std::ifstream file;
    std::vector<int*> pages;
    std::vector<bool> pageDirty;
    size_t pageFaults;
    size_t pageHits;
};

#endif
