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

#include "SIGA/SigaConverter/TimeSerieTreeSaver.h"

#include <fstream>
#include "SIGA/string-utils.h"

void TimeSerieTreeSaver::savetoDirectory(std::vector<std::vector<std::string>>& a_rows,
										 std::string a_fieldSeparator,
										 std::string a_outputDirectory,
										 std::string a_periodType)
{
	std::vector<std::vector<std::string>>::iterator it = a_rows.begin();
	std::vector<std::string> current = *it;
	int valueIndex = 1;
	for (const std::string& row : current)
	{
		std::string filename = a_outputDirectory + "\\" + row + a_periodType + ".srs";
		std::ofstream outputFile;
		bool skip = true;
		outputFile.open(filename);
		if (outputFile.is_open())
		{
			for (std::vector<std::string>& values: a_rows)
			{
				if (skip == true)
				{
					skip = false;
					continue;
				}
				outputFile << values[0] << a_fieldSeparator;
				outputFile << values[valueIndex] << "\n";
			}
		}
		outputFile.close();
		++valueIndex;
	}
}

void save(std::vector<std::vector<std::string>>& a_rows,
		  std::string a_fieldSeparator,
		  std::string a_outputFile,
		  bool a_addHeader,
		  std::string a_periodType)
{
	bool skip = a_addHeader ? false : true;
	std::ofstream outputFile;
	outputFile.open(a_outputFile);
	if (outputFile.is_open())
	{
		for (std::vector<std::string>& row: a_rows)
		{
			if (skip == true)
			{
				skip = false;
				continue;
			}
			std::string rowStr;
			StringUtils::join(rowStr, row, a_fieldSeparator);
			outputFile << rowStr << "\n";
		}
	}
	outputFile.close();
}

void TimeSerieTreeSaver::savetoFile(std::vector<std::vector<std::string>>& a_rows,
									std::string a_fieldSeparator,
									std::string a_outputFile,
									std::string a_periodType)
{
	if (a_outputFile.find("_diario") != std::string::npos
		|| a_outputFile.find("_mensal") != std::string::npos
		|| a_outputFile.find("_anual") != std::string::npos)
	{
		a_periodType = "";
	}
	StringUtils::replace(a_outputFile, ".", a_periodType + ".");
	save(a_rows,  a_fieldSeparator, a_outputFile, false, a_periodType);
}


void TimeSerieTreeSaver::savetoFileWithHeader(std::vector<std::vector<std::string>>& a_rows,
											  std::string a_fieldSeparator,
											  std::string a_outputFile,
											  std::string a_periodType)
{
	StringUtils::replace(a_outputFile, ".", a_periodType + ".");
	save(a_rows,  a_fieldSeparator, a_outputFile, true, a_periodType);
}
