#include "FileUtils.h"

#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

bool createDirectory(const std::string& path) {
#ifdef _WIN32
    if (_mkdir(path.c_str()) == 0) return true;
#else
    if (mkdir(path.c_str(), 0777) == 0) return true;
#endif
    return false;
}