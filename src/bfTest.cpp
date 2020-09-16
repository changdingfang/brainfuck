// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     bfTest.cpp
// Author:       dingfang
// CreateDate:   2020-09-15 20:09:13
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-16 19:28:02
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include "brainfuck.h"
#include "cmdline.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include <string>

using namespace std;

void parseFile(const string &filename, string &ist)
{
    std::FILE *pFd = ::fopen(filename.c_str(), "r");
    if (pFd == nullptr)
    {
        throw(string("open bf file error"));
    }
    int fd = ::fileno(pFd);
    struct stat64 st;
    fstat64(fd, &st);
    ist.resize(st.st_size);
    size_t pos = 0;
    int ret = 0;
    while ((ret = std::fread(const_cast<char *>(ist.data()) + pos, 1, 1024, pFd)))
    {
        pos += ret;
    }
}


int main(int argc, char **argv)
{
    CmdLine cl;
    string ist;
    try
    {
        cl.parseCmdLine(argc, argv);
        // cl.print();
        parseFile(cl.get("bffile"), ist);
    }
    catch (const string e)
    {
        perror(e.c_str());
        exit(-1);
    }

    struct timeval t1;
    gettimeofday(&t1, nullptr);

    bf::BF bf;
    bf.setSleepTime(std::stoul(cl.get("sleepTime", "15")));
    bf.parseInstructions(ist);

    struct timeval t2;
    gettimeofday(&t2, nullptr);

    time_t useTime = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
    printf("use time: %lu(ms)\n", useTime);

    return 0;
}
