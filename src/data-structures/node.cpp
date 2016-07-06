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

/** Public Methods **/

using namespace SIGA::DS;

Node::Node(int label,
           Node *node)
{
    m_label = label;
    if (node != nullptr)
    {
        m_parent = node;
        if (node->child() == nullptr)
        {
            node->setChild(*this);
        }
        else
        {
            Node* current = node->child();
            while (current->next() != nullptr)
            {
                current = current->next();
            }
            current->setNext(*this);
            m_previous = current;
        }
    }
}

VectorOfInt &Node::identifiers()
{
    return m_ids;
}

/*!
 * Todo: you must test it
 */
int Node::valuesSize()
{
    return m_values.rows() * m_values.cols();
}


void Node::setPrevious(Node &previous)
{
    m_previous = &previous;
}

void Node::setNext(Node &next)
{
    m_next = &next;
}

void Node::setChild(Node &child)
{
    m_child = &child;
}

Node *Node::parent() const
{
    return m_parent;
}

Node *Node::previous() const
{
    return m_previous;
}

Node *Node::next() const
{
    return m_next;
}

Node *Node::child() const
{
    return m_child;
}

