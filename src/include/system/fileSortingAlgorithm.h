#ifndef FILESORTINGALGORITHMSYSTEM_H
#define FILESORTINGALGORITHMSYSTEM_H

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileSortingAlgorithm {
public:
    FileSortingAlgorithm(std::string path);

    std::vector<fs::directory_entry> entries;

    // éventuellement :
    void sortByName();
    void sortByDate();
    void sortBySize();
};

#endif