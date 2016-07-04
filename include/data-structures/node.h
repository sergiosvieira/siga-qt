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
        using PtrFloatOfSparseMatrix = SparseMatrix<float*>;
        /*!
         * \brief The Node class
         * Store important node's variables like: label, identifiers, values and next node
         * pointer
         */
        class Node
        {
        public:
            /*!
             * \brief Default Constructor
             * \param label
             * \param next
             */
            Node(int label,
                 Node* next = nullptr);
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
                                   long col) const
            {
                return m_matrix[row][col];
            }
            /*!
             * \brief Values container size
             * \return Integer Value (Rows * Cols of sparse matrix)
             */
            int valuesSize();
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
                return (label < other.label());
            }
        protected:
            int m_label;
            VectorOfInt m_ids;
            PtrFloatOfSparseMatrix m_values;
            Node* m_next = nullptr;
        };
    }
}

#endif // __NODE__
