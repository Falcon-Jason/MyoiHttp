//
// Created by jason on 3/6/21.
//

#ifndef MYOIHTTP_FILEINFO_H
#define MYOIHTTP_FILEINFO_H

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

        void resetFile(const char *filename);

        [[nodiscard]] bool exists() const;

        [[nodiscard]] bool readable() const;

        [[nodiscard]] size_t size() const;

        [[nodiscard]] const char *mime() const;

        [[nodiscard]] const char *filename() const;
    };
}

#endif //MYOIHTTP_FILEINFO_H
