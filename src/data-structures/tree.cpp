/****************************************************************************
 Copyright (c) 2016 Funceme
 Author: Sérgio Vieira - sergiosvieira@gmail.com

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

#include "../../include/data-structures/tree.h"
#include <iostream>
#include <stdio.h>

using namespace SIGA::DS;
using namespace std;


shared_ptr<Node> Tree::find(int label)
{
    return nullptr;
}

shared_ptr<Node> Tree::add(int label,
                           shared_ptr<Node> parent)
{
    if (m_root == nullptr)
    {
        m_root = make_shared<Node>(label);
        m_first = m_last = m_root;
        return m_root;
    }
    if (parent != nullptr)
    {
        m_last = make_shared<Node>(label);
        if (parent->child() == nullptr)
        {
            parent->setChild(m_last);
        }
        else
        {
            shared_ptr<Node> current = parent->child();
            while(current->next() != nullptr)
            {
                current = current->next();
            }
            current->setNext(m_last);
        }
        return m_last;
    }
    return nullptr;
}
