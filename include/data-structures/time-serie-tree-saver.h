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

#ifndef __TIME_SERIE_TREE_SAVER__
#define __TIME_SERIE_TREE_SAVER__

#include "time-serie-tree-formatter.h"

#include <tuple>


using namespace SIGA::DS;

namespace SIGA
{
    namespace DS
    {
        class TimeSerieTreeSaver
        {
        public:
            /*!
             * Predefined types
             */
            using SeparatorDirectoryTypeOutput = tuple<string, string, string>;
            /*!
             * \brief save matrix of string to directory
             * \param rows
             * \param options
             */
            static void savetoDirectory(TimeSerieTreeFormatter::MatrixOfString& rows,
                                        SeparatorDirectoryTypeOutput& options);
            /*!
             * \brief save matrix of string to file
             * \param rows
             * \param options
             */
            static void savetoFile(TimeSerieTreeFormatter::MatrixOfString& rows,
                                   SeparatorDirectoryTypeOutput& options);
            /*!
             * \brief save matrix of string to file with header
             * \param rows
             * \param options
             */
            static void savetoFileWithHeader(TimeSerieTreeFormatter::MatrixOfString& rows,
                                             SeparatorDirectoryTypeOutput& options);
        private:
            /*!
             * \brief internal save method
             * \param rows
             * \param fieldSeparator
             * \param outputFile
             * \param addHeader
             * \param periodType
             */
            static void save(TimeSerieTreeFormatter::MatrixOfString& rows,
                             std::string fieldSeparator,
                             std::string outputFile,
                             bool addHeader,
                             std::string periodType);
        };
    }
}

#endif /** __TIME_SERIE_TREE_SAVER__ **/
