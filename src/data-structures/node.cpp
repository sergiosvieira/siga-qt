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

#include "../../include/data-structures/node.h"
#include <stdio.h>

using namespace SIGA::DS;
using namespace std;

/** Public Methods **/
Node::Node(int label): m_label(label)
{
}

void Node::setNext(shared_ptr<Node> next)
{
    m_next = next;
}

void Node::setChild(shared_ptr<Node> child)
{
    m_child = child;
}

shared_ptr<Node> Node::next()
{
    return m_next;
}

shared_ptr<Node> Node::child()
{
    return m_child;
}

shared_ptr<Node> Node::parent()
{
    return m_parent.lock();
}

void Node::setParent(shared_ptr<Node> parent)
{
    m_parent = parent;
}

shared_ptr<Node> Node::previous()
{
    return m_previous.lock();
}

void Node::setPrevious(shared_ptr<Node> previous)
{
    m_previous = previous;
}

