// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     bfTest.cpp
// Author:       dingfang
// CreateDate:   2020-09-15 20:09:13
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-17 22:45:31
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include "brainfuck.h"
#include "cmdline.h"
#include "format.h"

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


void writeFile(const string &filename, const string &data)
{
    std::FILE *pFd = ::fopen(filename.c_str(), "w+");
    if (pFd == nullptr)
    {
        throw(string("open bf file error"));
    }
    std::fwrite(const_cast<char *>(data.data()), 1, data.size(), pFd);
}


int main(int argc, char **argv)
{
    CmdLine cl;
    string ist;
    try
    {
        cl.parseCmdLine(argc, argv);
        // cl.print();
        string filename = cl.get("format", "");
        if (!filename.empty())
        {
            parseFile(filename, ist);
            string formatIst;
            bf::Format fm;
            fm.format(ist, formatIst);
            string newFile = cl.get("output", "");
            if (newFile.empty())
            {
                newFile = filename.substr(0, filename.find_last_of('.')) + "_new.b";
            }
            writeFile(newFile, formatIst);
            printf("format success, new file: %s\n", newFile.c_str());

            return 0;
        }

        filename = cl.get("bffile");
        parseFile(filename, ist);
    }
    catch (const string e)
    {
        perror(e.c_str());
        exit(-1);
    }


    struct timeval t1;
    gettimeofday(&t1, nullptr);

    if (cl.get("show", "true") == "true")
    {
        Window w(ist);
        w.setSleepTime(std::stoul(cl.get("sleepTime", "15")));
        bf::BF bf(&w);
        bf.parseInstructions(ist);
    }
    else
    {
        bf::BF bf;
        bf.parseInstructions(ist);
    }

    struct timeval t2;
    gettimeofday(&t2, nullptr);

    time_t useTime = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
    printf("use time: %lu(ms)\n", useTime);

    return 0;
}
