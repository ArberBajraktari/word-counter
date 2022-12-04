#include <iostream>
#include <vector>
#include <filesystem>
#include <map> // A map will be used to count the words.
#include <fstream> // Will be used to read from a file.
#include <sstream>

namespace fs = std::__fs::filesystem;


/**
 * \brief   Used for debugging
 */
template <class KTy, class Ty>
 void PrintMap(std::map<KTy, Ty> map){
    typedef typename std::map<KTy, Ty>::iterator iterator;
    for (iterator p = map.begin(); p != map.end(); p++)
        std::cout << p->first << ": " << p->second << std::endl;
}

/**
 * \brief   Used for debugging
 */
template <class _T1, class _T2>
void PrintVector(std::vector<std::pair<_T1, _T2>> &vec){
    for (auto i: vec)
        std::cout << i.first << " -> " << i.second <<std::endl;
}

/**
 * \brief   Return the filenames of all files that have the specified extension
 *          in the specified directory and all subdirectories.
 */
auto getAllFiles = [](fs::path const &root, std::string const &ext){
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
};

/**
 * \brief   This function counts the words and returns a map of them
 */
auto countWords = [](const std::string &fileName) {
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

/**
 * \brief   This function adds a map into another map and returns the result
 */
auto addMapToMap = [](std::map<std::string, unsigned int> &first_map, std::map<std::string, unsigned int> &second_map){

    for (auto const& [key, val] : second_map)
    {
        //Look if it's already there.
        if (first_map.find(key) == first_map.end()) // Then we've encountered the word for a first time.
            first_map[key] += second_map[key];
        else // Then we've already seen it before.
            first_map[key]++; // Just increment it.
    }

    return first_map;
};

/**
 * \brief   Loop through all the files that were found in the specified directory
 *          and save the words and their count in a map
 */
auto loopFiles =[](const std::vector<std::string> &files){
    std::map<std::string, unsigned int> allFilesWords;
    for (auto it = begin (files); it != end (files); ++it) {
        std::map<std::string, unsigned int> temp = countWords( *it);
        allFilesWords = addMapToMap(allFilesWords, temp);
    }
    return allFilesWords;
};

/**
 * \brief   Returns a stringstream version of all the result in this format:
 *          "word" -> "count"
 *          In a descending order
 */
auto getResult = [](std::vector<std::pair<std::string, int >> &vec) {
    std::stringstream temp;
    for (auto i: vec){
        temp << i.first;
        temp << " -> ";
        temp << i.second;
        temp << std::endl;
    }
    return temp;
};

/**
 * \brief   This is a compare function used as a parameter for the sorting of the
 *          map/vector<pair>
 *          It helps us sort in a descending order
 */
bool cmp(std::pair<std::string, int> &a, std::pair<std::string, int> &b){
    return a.second > b.second;
}

/**
 * \brief   This function converts a map into a vector and then sorts it
 */
auto sortMap = [](const std::map<std::string, unsigned int> &map){
    // Declare vector of pairs
    std::vector<std::pair<std::string, int> > temp;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : map) {
        temp.push_back(it);
    }

    // Sort using comparator function
    sort(temp.begin(), temp.end(), cmp);

    return temp;
};


int main() {
    // Declare vars that will be used below
    std::string path;
    std::string ext;
    std::map<std::string, unsigned int> map;
    std::vector<std::pair<std::string, int >> results;
    std::stringstream res;

    // Get path and extension from user
    std::cout << "Enter path please: ";
    std::cin >> path;
    std::cout << "Enter extension please: ";
    std::cin >> ext;

    // Get all files recursively from the directory
    // From subdirectories as well
    std::vector<std::string> allFiles = getAllFiles(path, ext);

    // Save all the words and occurrences in a map<string, int>
    map = loopFiles(allFiles);

    // Convert the map into a vector of pairs, as it is easier to
    // sort it from the value compared to a map
    results = sortMap(map);

    // Convert the Vector of pairs into a stringstream
    res = getResult(results);

    // Display the Result
    std::cout << "The end result:" <<std::endl;
    std::cout << res.str();
}