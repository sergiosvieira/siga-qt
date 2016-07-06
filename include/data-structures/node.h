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

#ifndef __NODE__
#define __NODE__

/** STL **/
#include <vector>

#include <memory>

using namespace std;


/*!
 * SIGA Namespace
 */
namespace SIGA
{
    /*!
     * Data Structure Namespace
     */
    namespace DS
    {
        /*!
         * \brief The Node class
         * Store important node's variables like: label, identifiers, values and next node
         * pointer
         */
        class Node
        {
        public:
            Node(int label);
            /*!
             * \brief Node's label
             * \return Integer Value
             */
            inline int label() const
            {
                return m_label;
            }
            /*!
             * \brief Set smart pointer to its next node
             * \param next
             */
            void setNext(shared_ptr<Node> next);
            /*!
             * \brief Set smart pointer to its child
             * \param child
             */
            void setChild(shared_ptr<Node> child);
            /*!
             * \brief Pointer to next node
             * \return
             */
            shared_ptr<Node> next();
            /*!
             * \brief Pointer to child node
             * \return
             */
            shared_ptr<Node> child();
            /*!
             * \brief Returns smart pointer to its parent
             * \return
             */
            shared_ptr<Node> parent();
            /*!
             * \brief Set smart pointer to its parent
             * \param parent
             */
            void setParent(shared_ptr<Node> parent);
            /*!
             * \brief Returns smart pointer to its previous node
             * \return
             */
            shared_ptr<Node> previous();
            /*!
             * \brief Set smart pointer to its previous node
             * \param previous
             */
            void setPrevious(shared_ptr<Node> previous);

            /*!
             * \brief Operator == overloading
             * \param other
             * \return Boolean Value
             */
            bool operator==(const shared_ptr<Node>& other) const
            {
                return (m_label == other->label());
            }
            /*!
             * \brief Operator < overloading
             * \param other
             * \return Boolean Value
             */
            bool operator<(const shared_ptr<Node>& other) const
            {
                return (m_label < other->label());
            }            
        protected:
            int m_label;
            weak_ptr<Node> m_parent;
            weak_ptr<Node> m_previous;
            shared_ptr<Node> m_next = nullptr;
            shared_ptr<Node> m_child = nullptr;
        };
    }
}

#endif // __NODE__
