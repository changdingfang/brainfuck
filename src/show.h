// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     show.h
// Author:       dingfang
// CreateDate:   2020-09-15 19:22:08
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-15 20:09:33
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifndef __SHOW_H__
#define __SHOW_H__


#include <stdio.h>

#include <string>
#include <vector>

constexpr int LinesMax = 12;

using namespace std;

class Window
{
public:
    Window(string bfCode, size_t windowSize = 15)
        : windowSize_ (windowSize)
          , top_(" ")
          , bottom_(" ")
    {
        string::size_type pos = 0, pos2 = 0;
        while (true)
        {
            pos2 = bfCode.find_first_of('\n', pos);
            if (pos2 == string::npos)
            {
                break;
            }
            bfCode_.push_back(bfCode.substr(pos, pos2 - pos + 1));
            pos = pos2 + 1;
        }

        for (int i = 0; i <= windowSize_; ++i)
        {
            top_ += "_ _ ";
            bottom_ += "----";
        }
        top_ += '\n';
        bottom_ += '\n';
    }


    void show(vector<unsigned char> v, size_t ptrIndex, string::size_type codeIndex)
    {
        system("clear");
        this->showPaperTape(v, ptrIndex);
        this->showOutput();
        this->showcode(codeIndex);
    }


    void output(unsigned char ch)
    {
        output_.append(1, ch); 
    }


    void windowsShiftRight(size_t ptIndex)
    {
        if (ptIndex < start_)
        {
            --start_;
            --end_;
        }
    }


    void windowsShiftLeft(size_t ptIndex)
    {
        if (ptIndex > end_)
        {
            ++start_;
            ++end_;
        }
    }


private:
    void showOutput()
    {
        printf("output: %s\n", output_.c_str());
    }


    void showPaperTape(vector<unsigned char> v, size_t ptrIndex)
    {
        printf("%s", top_.c_str());
        for (size_t i = start_; i <= end_; ++i)
        {
            if (i < v.size())
            {
                v[i] < 10 ? printf("| %-2d", v[i]) : printf("|%-3d", v[i]);
                continue;
            }
            printf("| %-2d", 0);
        }
        printf("|\n");
        printf("%s", bottom_.c_str());
        string ptr;
        ptr.assign((ptrIndex - start_) * 4, ' ');
        printf("%s  |[%lu]\n", ptr.c_str(), ptrIndex);
    }


    void showcode(string::size_type codeIndex)
    {
        printf("====================== bf code ==========================\n");
        int printLinedCount = 0;
        string::size_type realIndex = codeIndex;
        for (size_t line = 0; line < bfCode_.size(); ++line)
        {
            if (realIndex >= bfCode_[line].size())
            {
                realIndex -= bfCode_[line].size();
                continue;
            }

            for (size_t preLine = 5; preLine > 0; --preLine)
            {
                if (preLine < line)
                {
                    printf("%lu  %s", line - preLine + 1, bfCode_[line - preLine].c_str());
                    ++printLinedCount;
                }
            }
            printf("%lu  %s\033[7;33;40m%c\033[0m%s"
                    , line + 1
                    , bfCode_[line].substr(0, realIndex).c_str()
                    , bfCode_[line][realIndex]
                    , bfCode_[line].substr(realIndex + 1,string::npos).c_str());
            for (size_t nextLine = 1; printLinedCount < LinesMax; ++nextLine)
            {
                ++printLinedCount;
                if (line + nextLine < bfCode_.size())
                {
                    printf("%lu  %s", line + nextLine + 1, bfCode_[line + nextLine].c_str());
                    continue;
                }
                printf("\n");
            }
            break;
        }
        printf("=========================================================\n");
    }


private:
    size_t start_ = 0;
    size_t end_ = 15;
    size_t windowSize_;
    string top_;
    string bottom_;
    string output_;
    vector<string> bfCode_;
};


#endif /* __SHOW_H__ */
