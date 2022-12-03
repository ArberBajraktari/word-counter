#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <filesystem>

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


int main() {
    std::vector<std::string> all = getAllFiles("/Users/agron/Desktop", ".html");
    std::cout << "Number of files is: " << all.size() << std::endl;
}
