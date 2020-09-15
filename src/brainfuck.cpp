// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// FileName:     brainfuck.cpp
// Author:       dingfang
// CreateDate:   2020-09-15 20:07:46
// ModifyAuthor: dingfang
// ModifyDate:   2020-09-15 20:14:24
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include "brainfuck.h"


using namespace std;


namespace bf
{


    BF::BF()
        : paperTape_()
          , ptIndex_(0)
    {
        paperTape_.resize(1024, 0);
    }


    void BF::removeInvalidChar_(const string &ist, string &realIst)
    {
        for (string::size_type i = 0; i < ist.size(); ++i)
        {
            if (ist[i] == BF_PLUS
                    || ist[i] == BF_MINUS
                    || ist[i] == BF_PREVIOUS
                    || ist[i] == BF_NEXT
                    || ist[i] == BF_OUTPUT
                    || ist[i] == BF_INPUT
                    || ist[i] == BF_LOOP_START
                    || ist[i] == BF_LOOP_STOP)
            {
                realIst.push_back(ist[i]);
            }
        }
    }


    bool BF::grammarCheck(const string &ist) const
    {
        size_t loopStart = 0, loopStop = 0, linePos = 0, lineNum = 1;

        for (string::size_type i = 0; i < ist.size(); ++i)
        {
            if (ist[i] == '\n')
            {
                ++lineNum;
                linePos = i + 1;
            }

            if (ist[i] == BF_LOOP_START)
            {
                ++loopStart;
            }
            else if (ist[i] == BF_LOOP_STOP)
            {
                ++loopStop;
                if (loopStart < loopStop)
                {
                    string err("Mismatched parentheses! on ");
                    err.append(std::to_string(lineNum)).append(" line \"");
                    err.append(ist.substr(linePos, ist.find_first_of('\n', linePos) - linePos));
                    err.append("\"");
                    throw(err);
                }
            }
        }

        if (loopStart != loopStop)
        {
            throw(string("Mismatched parentheses!"));
        }

        return true;
    }


    void BF::parseInstructions(const string &srcIst)
    {
        try
        {
            this->grammarCheck(srcIst);
        }
        catch (const string e)
        {
            printf("%s\n", e.c_str());
            exit(-1);
        }

        string ist(srcIst);
        Window w(srcIst);

        // this->removeInvalidChar_(srcIst, ist);

        for (string::size_type i = 0; i < ist.size(); ++i)
        {
            switch(ist[i])
            {
                case BF_PLUS:       ++paperTape_[ptIndex_];     break;
                case BF_MINUS:      --paperTape_[ptIndex_];     break;
                case BF_PREVIOUS:   this->previous_(w);         break;
                case BF_NEXT:       this->next_(w);             break;
                case BF_OUTPUT: w.output(paperTape_[ptIndex_]); break;
                case BF_INPUT:  paperTape_[ptIndex_] = getchar(); break;
                case BF_LOOP_START: loop_.push(i);               break;
                case BF_LOOP_STOP: 
                    {
                        string::size_type top = this->loopStop_(w);
                        if (top != 0)
                        {
                            w.show(paperTape_, ptIndex_, i);
                            usleep(SLEEP_TIME);
                            i = top;
                            continue;
                        }
                        break;
                    }
                default:
                    continue;
            }
            w.show(paperTape_, ptIndex_, i);
            usleep(SLEEP_TIME);
        }
    }


}; /* namespace end of bf */
