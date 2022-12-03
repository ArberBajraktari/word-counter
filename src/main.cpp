#include <iostream>
#include <vector>
#include <filesystem>
#include <map> // A map will be used to count the words.
#include <fstream> // Will be used to read from a file.
#include <string> // The map's key value.
#include <sstream>

namespace fs = std::__fs::filesystem;


/**
 * \brief   Return the filenames of all files that have the specified extension
 *          in the specified directory and all subdirectories.
 *
 */
std::vector<std::string> getAllFiles(fs::path const & root, std::string const & ext)
{
    std::vector<std::string> paths;

    if (fs::exists(root) && fs::is_directory(root))
    {
        for (auto const & entry : fs::recursive_directory_iterator(root))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext)
                paths.emplace_back(entry.path());
        }
    }
    return paths;
}


//Will be used to print the map later.
template <class KTy, class Ty>
void PrintMap(std::map<KTy, Ty> map)
{
    typedef typename std::map<KTy, Ty>::iterator iterator;
    for (iterator p = map.begin(); p != map.end(); p++)
        std::cout << p->first << ": " << p->second << std::endl;
}

std::map<std::string, unsigned int> wordCount(const std::string &fileName) {
    // "C:\\Users\\user\\Documents\\MyFile.txt"

    // Will store the word and count.
    std::map<std::string, unsigned int> wordsCount;
    {
        // Begin reading from file:
        std::ifstream fileStream(fileName);

        // Check if we've opened the file (as we should have).
        if (fileStream.is_open())
            while (fileStream.good())
            {
                // Store the next word in the file in a local variable.
                std::string word;
                fileStream >> word;

                //Look if it's already there.
                if (wordsCount.find(word) == wordsCount.end()) // Then we've encountered the word for a first time.
                    wordsCount[word] = 1; // Initialize it to 1.
                else // Then we've already seen it before.
                    wordsCount[word]++; // Just increment it.
            }
        else  // We couldn't open the file. Report the error in the error stream.
        {
            std::stringstream consoleOutput;
            consoleOutput << "Cant";
            consoleOutput << "Open";
            return wordsCount;
        }
    }
    return wordsCount;
};


std::map<std::string, unsigned int> addMapToMap(std::map<std::string, unsigned int> first_map, std::map<std::string, unsigned int> second_map){

    for (auto const& [key, val] : second_map)
    {
        //Look if it's already there.
        if (first_map.find(key) == first_map.end()) // Then we've encountered the word for a first time.
            first_map[key] += second_map[key];
        else // Then we've already seen it before.
            first_map[key]++; // Just increment it.
    }

    return first_map;
}

std::map<std::string, unsigned int> loopFiles(const std::vector<std::string> files){
    std::map<std::string, unsigned int> allFilesWords;
    for (auto it = begin (files); it != end (files); ++it) {
        std::map<std::string, unsigned int> temp = wordCount( *it);
        allFilesWords = addMapToMap(allFilesWords, temp);
    }

    return allFilesWords;
}

bool cmp(std::pair<std::string, int>& a,
         std::pair<std::string, int>& b)
{
    return a.second < b.second;
}

std::map<std::string, unsigned int> sortMap(const std::map<std::string, unsigned int> &M){
    // Declare vector of pairs
    std::vector<std::pair<std::string, int> > A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    std::map<std::string, unsigned int> map;
    std::copy(A.begin(), A.end(), std::inserter(map, map.begin()));

    return map;

}

int main() {
    std::string path;
    std::string ext;
    std::cout << "Enter path please: ";
    std::cin >> path;
    std::cout << "Enter extension please: ";
    std::cin >> ext;
    std::vector<std::string> allFiles = getAllFiles(path, ext);
    std::cout << allFiles.size() << std::endl;
    //wordCount(fileName);
    std::map<std::string, unsigned int> map;
    map = loopFiles(allFiles);
    map = sortMap(map);

    PrintMap(map);
}

