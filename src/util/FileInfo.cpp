/**
 * @file FileInfo.cpp
 * @author Jason Cheung
 * @date 2021.06.03
 * @brief The class encapsulated file information APIs (`stat/fstat`).
 */

#include "util/FileInfo.h"

#include <map>
#include <string>
#include <cassert>
#include <cstring>

namespace myoi {
    using std::map, std::string;
    const static map<string, const char *> mimes{
            {".html", "text/html"},
            {".htm", "text/html"},
            {".gif", "image/gif"},
            {".png", "image/png"},
            {".jpg", "image/jpeg"},
            {".jpeg", "image/jpeg"}
    };

    const char *defaultMime{"text/plain"};

    FileInfo::FileInfo(const char *filename) {
        setFile(filename);
    }

    void FileInfo::setFile(const char *filename) {
        fileName_ = filename;
        auto ret = ::stat(filename, &fileStat_);
        exists_ = (ret == 0);
    }

    bool FileInfo::exists() const {
        return exists_;
    }

    bool FileInfo::readable() const {
        assert(exists());
        return S_ISREG(fileStat_.st_mode) && (S_IRUSR & fileStat_.st_mode);
    }

    size_t FileInfo::size() const {
        assert(exists());
        return fileStat_.st_size;
    }

    const char * FileInfo::filename() const {
        return fileName_.c_str();
    }

    const char * FileInfo::mime() const {
        auto pos = ::strrchr(fileName_.c_str(), '.');
        if (pos != nullptr && mimes.count(pos)) {
            return mimes.at(pos);
        } else {
            return defaultMime;
        }
    }
}