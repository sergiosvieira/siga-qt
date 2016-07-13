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

#include "../../include/data-structures/time-serie-tree-saver.h"

#include <fstream>

#include "../../include/utils/string-utils.h"


using namespace SIGA::DS;

void TimeSerieTreeSaver::savetoDirectory(TimeSerieTreeFormatter::MatrixOfString& rows,
                                         SeparatorDirectoryTypeOutput &options)
{
    std::vector<std::vector<std::string>>::iterator it = rows.begin();
	std::vector<std::string> current = *it;
	int valueIndex = 1;
    string outputDirectory = get<1>(options);
    string periodType = get<2>(options);
    string separator = get<0>(options);
	for (const std::string& row : current)
	{
        std::string filename = outputDirectory + "\\" + row + periodType + ".srs";
		std::ofstream outputFile;
		bool skip = true;
		outputFile.open(filename);
		if (outputFile.is_open())
		{
            for (std::vector<std::string>& values: rows)
			{
				if (skip == true)
				{
					skip = false;
					continue;
				}
                outputFile << values[0] << separator;
				outputFile << values[valueIndex] << "\n";
			}
		}
		outputFile.close();
		++valueIndex;
	}
}

void TimeSerieTreeSaver::save(TimeSerieTreeFormatter::MatrixOfString& rows,
                              std::string fieldSeparator,
                              std::string outputFile,
                              bool addHeader,
                              std::string periodType)
{
    bool skip = addHeader ? false : true;
    std::ofstream oFile;
    oFile.open(outputFile);
    if (oFile.is_open())
	{
        for (std::vector<std::string>& row: rows)
		{
			if (skip == true)
			{
				skip = false;
				continue;
			}
			std::string rowStr;
            StringUtils::join(rowStr, row, fieldSeparator);
            oFile << rowStr << "\n";
		}
	}
    oFile.close();
}

void TimeSerieTreeSaver::savetoFile(TimeSerieTreeFormatter::MatrixOfString& rows,
                                    SeparatorDirectoryTypeOutput &options)
{
    string separator = get<0>(options);
    string outputFile = get<1>(options);
    string periodType = get<2>(options);
    if (outputFile.find("_diario") != std::string::npos
        || outputFile.find("_mensal") != std::string::npos
        || outputFile.find("_anual") != std::string::npos)
	{
        periodType = "";
	}
    StringUtils::replace(outputFile, ".", periodType + ".");
    save(rows,  separator, outputFile, false, periodType);
}


void TimeSerieTreeSaver::savetoFileWithHeader(TimeSerieTreeFormatter::MatrixOfString &rows,
                                              SeparatorDirectoryTypeOutput& options)
{
    string separator = get<0>(options);
    string outputFile = get<1>(options);
    string periodType = get<2>(options);
    StringUtils::replace(outputFile, ".", periodType + ".");
    save(rows, separator, outputFile, true, periodType);
}
