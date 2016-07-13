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

#ifndef __TIME_SERIE_TREE_FORMATTER__
#define __TIME_SERIE_TREE_FORMATTER__

/** SIGA **/
#include "time-serie-tree.h"

/** STL **/
#include <vector>
#include <tuple>
#include <string>
#include <functional>

using namespace SIGA::DS;

namespace SIGA
{
    namespace DS
    {
        class TimeSerieTreeFormatter
        {
        public:
                /*! InputStructure
                 *  \param PeriodType (NONE = 0x0000, HOURLY_TYPE  = 0x1111, DAILY_TYPE  = 0x0111, MONTHLY_TYPE  = 0x0011, YEARLY_TYPE  = 0x0001)
                 *  \param DateFormat - std::string (Examples: dd/mm/yyyy, mm/yyyy, yyyy)
                 *  \param Field Separator - std::string (Examples: "," "\t")
                 */
                using TypeFormatSeparatorInput = std::tuple<PeriodType, string, string>;
                using MatrixOfString = std::vector<std::vector<std::string>>;
                using ValueFunction = std::function<void(std::string)>;
                /*!
                 * \brief matrix
                 * \param tree
                 * \param options
                 * \return
                 */
                /*! To do: is it necessary? */
//                static MatrixOfString matrix(TimeSerieTree& tree,
//                                             const Input& options);
                /*!
                 * \brief serie
                 * \param tree
                 * \param options
                 * \param progress
                 * \return
                 */
                static MatrixOfString serie(TimeSerieTree& tsTree,
                                            const TypeFormatSeparatorInput& options,
                                            std::function<bool(long, long)> progress);
        private:

                static CDate dateFromTreeDepth(const TreeNode& node,
                                               const int& depth);
                static int treeDepthFromPeriodType(const PeriodType& a_periodType);
        };

    }
}

#endif /** __TIME_SERIE_TREE_FORMATTER__ **/
