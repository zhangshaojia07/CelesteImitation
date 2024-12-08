/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __OPTIONSLABEL_H__
#define __OPTIONSLABEL_H__

#include "cocos2d.h"

class OptionsLabel : public cocos2d::Label
{
public:
    static OptionsLabel* create(const std::string& string, float fontSize);
    void setActive(bool type);
    void setInactive();
};

class TickSender : public cocos2d::Ref
{
public:
    static TickSender* createWithParas(cocos2d::Scene* sender, float dt);
    void initWithParas(cocos2d::Scene* sender, float dt);
    void changeTarget(OptionsLabel* x);
    void flip(float dt);
protected:
    OptionsLabel* tar;
    bool status;
};

#endif // __OPTIONSLABEL_H__
