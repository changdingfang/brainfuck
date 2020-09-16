// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     cmdline.h
// Author:       dingfang
// CreateDate:   2020-09-16 19:26:54
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-16 13:23:49
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifndef __CMDLINE_H__
#define __CMDLINE_H__

#include <string.h>

#include <map>


/*
 * -f / --f / --format   filename
 * -o / --o / --output   filename
 * -d /
 * */
class CmdLine
{
public:
    void print()
    {
        for (const auto &it : paramMap_)
        {
            printf("%s : %s\n", it.first.c_str(), it.second.c_str());
        }
    }

    void parseCmdLine(int argc, char **argv)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (argv[i][0] == '-')
            {
                char *p = &argv[i][1];
                if (*p == '-')
                {
                    ++p;
                }

                if ((*p == 'h' && *(p + 1) == '\0') || !strcmp(p, "help"))
                {
                    this->printHelp();
                    exit(-1);
                }

                if (i + 1 >= argc)
                {
                    throw(std::string("param error!"));
                }

                if ((*p == 'f' && *(p + 1) == '\0') || !strcmp(p, "format"))
                {
                    paramMap_[format_] = argv[i + 1];
                }
                else if ((*p == 'o' && *(p + 1) == '\0') || !strcmp(p, "output"))
                {
                    paramMap_[output_] = argv[i + 1];
                }
                else if (*p == 'd' && *(p + 1) == '\0')
                {
                    paramMap_[sleepTime_] = argv[i + 1];
                }
                ++i;
            }
            else
            {
                paramMap_[bffile_] = argv[i];
            }
        }
    }

    inline std::string get(std::string key, std::string value = "")
    {
        auto it = paramMap_.find(key);
        if (it != paramMap_.end())
        {
            value = it->second;
        }

        return std::move(value);
    }

private:
    void printHelp()
    {
        printf("使用: ./bf brainfuckfile [option]\n");
        printf("示例: ./bf helloworld.b -d 10\n");
        printf("Options:\n");
        printf("\t-d / --d\t\t指令执行间隔(毫秒)\n");
        printf("\t-f / --f\t\t格式化bf文件\n");
        printf("\t-o / --o\t\t格式化bf文件后输出文件(新文件)\n");
        printf("\t-h / --h\t\t帮助\n");

    }

private:
    std::map<std::string, std::string> paramMap_;

    const std::string bffile_ {"bffile"};
    const std::string format_ {"format"};
    const std::string output_ {"output"};
    const std::string sleepTime_ {"sleepTime"};
};


#endif /* __CMDLINE_H__ */
