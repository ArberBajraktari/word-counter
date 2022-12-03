#include <iostream>
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
    std::string path;
    std::string ext;
    std::cout << "Enter path please: ";
    std::cin >> path;
    std::cout << "Enter extension please: ";
    std::cin >> ext;
    std::vector<std::string> allFiles = getAllFiles(path, ext);
    std::cout << allFiles.size() << std::endl;
}