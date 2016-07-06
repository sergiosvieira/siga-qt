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

#ifndef __TREE__
#define __TREE__

/** Data Structures **/
#include "node.h"


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
         * \brief The Tree class
         * Store nodes from time serie/matrix values
         */
        class Tree
        {
        public:
            /*!
             * \brief Find specified label
             * \param label
             * \return Node Pointer
             */
            Node* find(int label);
        protected:
            Node* m_root = nullptr;
            Node* m_first = nullptr;
            Node* m_last = nullptr;
        };
    }
}

#endif // __TREE__
