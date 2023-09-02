#pragma once
#include "noncopyable.h"
#include "MutexLock.h"
#include "FileUtil.h"
#include <memory>
#include <string>

// 提供自动归档功能
class LogFile : noncopyable {
    public:
    //每 append flushEveryN次  ， 会flush一下，会往文件写，只不过，文件也是带缓冲区的
    LogFile (const std::string& basename, int flushEveryN = 1024);
    ~LogFile ();

    void append (const char* logline, int len);
    void flush ();
    bool rollFile ();

    private:
    void append_unlocked (const char* logline, int len);

    const std::string basename_;
    const int flushEveryN_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
};
