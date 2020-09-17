// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     format.h
// Author:       dingfang
// CreateDate:   2020-09-17 19:28:14
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-17 21:25:49
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifndef __FORMAT_H__
#define __FORMAT_H__


#include "brainfuck.h"

#include <string>
#include <map>


namespace bf
{


class Format
{
public:
    /*
     * +++++++
     * */
    void format(const std::string &input, std::string &output)
    {
        int currLineLen = 0;
        std::map<char, int> ct {
            {BF_PLUS, 0},
            {BF_MINUS, 0},
            {BF_INPUT, 0},
            {BF_OUTPUT, 0},
            {BF_NEXT, 0},
            {BF_PREVIOUS, 0}
        };
        std::string currIndent("");

        for (std::string::size_type i = 0; i < input.size(); ++i)
        {
            if (input[i] != BF_PLUS
                    && input[i] != BF_MINUS
                    && input[i] != BF_PREVIOUS
                    && input[i] != BF_NEXT
                    && input[i] != BF_OUTPUT
                    && input[i] != BF_INPUT
                    && input[i] != BF_LOOP_START
                    && input[i] != BF_LOOP_STOP)
            {
                output.push_back(input[i]);
                continue;
            }

            if (input[i] == BF_LOOP_START || input[i] == BF_LOOP_STOP)
            {
                if (input[i] == BF_LOOP_START)
                {
                    output.push_back('\n');
                    output.append(currIndent);
                    currIndent.append("  ");
                }
                else if (input[i] == BF_LOOP_STOP)
                {
                    if (currIndent.size() >= 2)
                    {
                        currIndent.pop_back();
                        currIndent.pop_back();
                    }
                    output.push_back('\n');
                    output.append(currIndent);
                }
                output.push_back(input[i]);
                output.push_back('\n');
                output.append(currIndent);
                currLineLen = 0;
                continue;
            }

            int res = this->addCT_(ct, input[i]);
            if (res == 1 && i > 0)
            {
                if ((input[i - 1] == BF_PLUS
                        || input[i - 1] == BF_MINUS
                        || input[i - 1] == BF_INPUT
                        || input[i - 1] == BF_OUTPUT
                        || input[i - 1] == BF_NEXT
                        || input[i - 1] == BF_PREVIOUS))
                {
                    output.push_back(' ');
                }
            }
            output.push_back(input[i]);
            if (res == 5)
            {
                ct[input[i]] = 0;
            }

            if (++currLineLen > 80)
            {
                output.push_back('\n');
                output.append(currIndent);
                currLineLen = 0;
                ct[input[i]] = 0;
            }
        }
    }

private:
    int addCT_(std::map<char, int> &ct, char ist)
    {
        for (auto &it : ct)
        {
            if (it.first == ist)
            {
                ++it.second;
                continue;
            }
            it.second = 0;
        }
        return ct[ist];
    }
};


}; /* namespace end of df */


#endif /* __FORMAT_H__ */
