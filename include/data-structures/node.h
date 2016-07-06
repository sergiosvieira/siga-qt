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

/** Data Structures **/
#include "sparse-matrix.h"

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
        /** Predefined types **/
        using VectorOfInt = vector<int>;
        // Float pointer was choosen to sparse matrix no need store -999.0 values
        using PtrFloatOfSparseMatrix = SparseMatrix<float*>;
        /*!
         * \brief The Node class
         * Store important node's variables like: label, identifiers, values and next node
         * pointer
         */
        class Node
        {
        public:
            Node(int label,
                 Node* node = nullptr);
            /*!
             * \brief Value's identifiers
             * \return Vector of Integers
             */
            VectorOfInt& identifiers();
            /*!
             * \brief Node's label
             * \return Integer Value
             */
            inline int label() const
            {
                return m_label;
            }
            /*!
             * \brief Set value of the specified (row, col) in sparse matrix
             * \param row
             * \param col
             * \param value
             */
            void setValue(long row,
                          long col,
                          float* value = nullptr);
            /*!
             * \brief Get value of the specified (row, col) in sparse matrix
             * \param row
             * \param col
             * \return Float Pointer
             */
            inline float* getValue(long row,
                                   long col)
            {
                return m_values[row][col];
            }
            /*!
             * \brief Values container size
             * \return Integer Value (Rows * Cols of sparse matrix)
             */
            int valuesSize();
            /*!
             * \brief Set pointer to the previous node
             * \param previous
             */
            void setPrevious(Node &previous);
            /*!
             * \brief Set pointer to the next node
             * \param next
             */
            void setNext(Node &next);
            /*!
             * \brief Set pointer to the child
             * \param child
             */
            void setChild(Node &child);
            /*!
             * \brief Pointer to parent node
             * \return
             */
            Node *parent() const;
            /*!
             * \brief Pointer to previous node
             * \return
             */
            Node *previous() const;
            /*!
             * \brief Pointer to next node
             * \return
             */
            Node *next() const;
            /*!
             * \brief Pointer to child node
             * \return
             */
            Node *child() const;
            /*!
             * \brief Operator == overloading
             * \param other
             * \return Boolean Value
             */
            bool operator==(const Node& other) const
            {
                return (m_label == other.label());
            }
            /*!
             * \brief Operator < overloading
             * \param other
             * \return Boolean Value
             */
            bool operator<(const Node& other) const
            {
                return (m_label < other.label());
            }
        protected:
            int m_label;
            VectorOfInt m_ids;
            PtrFloatOfSparseMatrix m_values;
            Node* m_parent = nullptr;
            Node* m_previous = nullptr;
            Node* m_next = nullptr;
            Node* m_child = nullptr;
        };
    }
}

#endif // __NODE__
