#include "PagedArray.h"
#include <iostream>

PagedArray::PagedArray(const std::string& filePath, size_t size)
        : filePath(filePath), numElements(size), pageFaults(0), pageHits(0) {
    pageSize = 4096 / sizeof(int);  // Example page size
    numPages = (size + pageSize - 1) / pageSize;
    pages.resize(numPages, nullptr);
    pageDirty.resize(numPages, false);
}

PagedArray::~PagedArray() {
    for (size_t i = 0; i < numPages; ++i) {
        unloadPage(i);
    }
}

int& PagedArray::operator[](size_t index) {
    size_t pageIndex = index / pageSize;
    if (pages[pageIndex] == nullptr) {
        loadPage(pageIndex);
        ++pageFaults;
    } else {
        ++pageHits;
    }
    return pages[pageIndex][index % pageSize];
}

size_t PagedArray::getNumPageFaults() const {
    return pageFaults;
}

size_t PagedArray::getNumPageHits() const {
    return pageHits;
}

void PagedArray::loadPage(size_t pageIndex) {
    if (pages[pageIndex] == nullptr) {
        pages[pageIndex] = new int[pageSize];
        std::ifstream inputFile(filePath, std::ios::binary);
        inputFile.seekg(pageIndex * pageSize * sizeof(int));
        inputFile.read(reinterpret_cast<char*>(pages[pageIndex]), pageSize * sizeof(int));
        inputFile.close();
    }
}

void PagedArray::unloadPage(size_t pageIndex) {
    if (pages[pageIndex] != nullptr) {
        delete[] pages[pageIndex];
        pages[pageIndex] = nullptr;
    }
}
