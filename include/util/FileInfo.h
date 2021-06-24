/**
 * @file FileInfo.h
 * @author Jason Cheung
 * @date 2021.06.03
 * @brief The class encapsulated file information APIs (`stat/fstat`).
 */

#ifndef MYOI_FILEINFO_H
#define MYOI_FILEINFO_H


#include <sys/stat.h>
#include <string>

namespace myoi {
    class FileInfo {
    private:
        std::string fileName_{};
        struct stat fileStat_{};
        bool exists_{false};

    public:
        FileInfo() = default;

        explicit FileInfo(const char *filename);

        void setFile(const char *filename);

        [[nodiscard]] bool exists() const;

        [[nodiscard]] bool readable() const;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] const char *mime() const;

        [[nodiscard]] const char *filename() const;
    };
}


#endif //MYOI_FILEINFO_H
