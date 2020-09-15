// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     bfTest.cpp
// Author:       dingfang
// CreateDate:   2020-09-15 20:09:13
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-15 20:12:48
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include "brainfuck.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>
#include <string>

using namespace std;

void parseFile(const string &filename, string &ist)
{
    std::FILE *pFd = ::fopen(filename.c_str(), "r");
    if (pFd == nullptr)
    {
        throw("open bf file error");
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
    if (argc < 2)
    {
        perror("please input bf file");
        exit(-1);
    }
    string ist;
    parseFile(argv[1], ist);
    bf::BF bf;
    bf.parseInstructions(ist);

    return 0;
}
