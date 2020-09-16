// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     brainfuck.h
// Author:       dingfang
// CreateDate:   2020-09-15 20:07:03
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-16 19:33:12
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#ifndef __BRAINFUCK_H__
#define __BRAINFUCK_H__


#include "show.h"

#include <string>
#include <vector>
#include <stack>

namespace bf
{


    constexpr size_t SLEEP_TIME = 30 * 1000;

    constexpr char BF_PLUS      = '+';
    constexpr char BF_MINUS     = '-';
    constexpr char BF_PREVIOUS  = '<';
    constexpr char BF_NEXT      = '>';
    constexpr char BF_OUTPUT    = '.';
    constexpr char BF_INPUT     = ',';
    constexpr char BF_LOOP_START= '[';
    constexpr char BF_LOOP_STOP = ']';


    class BF
    {
    public:
        BF();
        void parseInstructions(const std::string &srcIst);


        inline void setSleepTime(time_t t)
        {
            sleepTime_ = t * 1000;
        }

    private:
        bool grammarCheck(const std::string &ist) const;


        inline void previous_(Window &w)
        {
            if (ptIndex_ == 0)
            {
                throw("Memory out of bounds");
            }
            --ptIndex_;
            w.windowsShiftRight(ptIndex_);
        }


        inline void next_(Window &w)
        {
            if (ptIndex_ >= paperTape_.size())
            {
                paperTape_.resize(2 * paperTape_.size(), 0);
            }
            ++ptIndex_;
            w.windowsShiftLeft(ptIndex_);
        }


        inline string::size_type loopStart_(const string &ist, string::size_type &i)
        {
            if (paperTape_[ptIndex_] != 0)
            {
                loop_.push(i);
                return i;
            }

            /* 1. */
            string::size_type pos = i;
            do
            {
                pos = ist.find_first_of(BF_LOOP_START, pos + 1);
                i = ist.find_first_of(BF_LOOP_STOP, i + 1);
            } while (i > pos);
            /* 2. */
            /*
            const char *ptr = ist.data();
            int count = 0;
            do
            {
                if (ptr[++i] == BF_LOOP_START)
                {
                    ++count;
                }
            } while (!(ptr[i] == BF_LOOP_STOP && --count == -1));
            */
            return i;
        }


        inline string::size_type loopStop_(string::size_type i)
        {
            if (paperTape_[ptIndex_] == 0)
            {
                loop_.pop();
                return i;
            }
            return (i = loop_.top());
        }


        void removeInvalidChar_(const std::string &ist, std::string &realIst);

    private:
        std::vector<unsigned char> paperTape_;
        size_t ptIndex_;
        stack<string::size_type> loop_;
        time_t sleepTime_ = {SLEEP_TIME};
    };


}; /* namespace end of bf */


#endif /* __BRAINFUCK_H__ */
