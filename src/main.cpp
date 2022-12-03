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
                paths.emplace_back(entry.path().filename());
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

int wordCount(const char* fileName) {
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
            return EXIT_FAILURE;
        }
        // Print the words map.
        PrintMap(wordsCount);
    }
    return EXIT_SUCCESS;
};



int main() {
    std::string path;
    std::string ext;
    std::cout << "Enter path please: ";
    std::cin >> path;
    std::cout << "Enter extension please: ";
    std::cin >> ext;
    std::vector<std::string> allFiles = getAllFiles(path, ext);
    std::cout << allFiles.size() << std::endl;

    static const char* fileName = "C:\\\\Users\\\\user\\\\Documents\\\\MyFile.txt";
    wordCount(fileName);
}

