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

#ifndef __SPARSE_MATRIX__
#define __SPARSE_MATRIX__

/** STL **/
#include <map>

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
         * Data structure to represents a Sparse Matrix
         */
        template<class T>
        class SparseMatrix: public map<long, map<long, T>>
        {
        public:
            /*!
             * \brief Returns the number of rows used in Sparse Matrix
             * \return Integer
             */
            int rows()
            {
                return this->size();
            }
            /*!
             * \brief Returns the max index column
             * \return
             */
            int cols()
            {
                int result = 0;
                for (typename Map::iterator it = this->begin();
                     it != this->end();
                     ++it)
                {
                    map<long, T> mapIn = it->second;
                    for (auto col: mapIn)
                    {
                        long key = col.first;
                        if (key > result)
                        {
                            result = key;
                        }
                    }
                }
                return result + 1;
            }
        private:
            using Map = map<long, map<long, T>>;
        };
    }
}
#endif /** __SPARSE_MATRIX__ **/
