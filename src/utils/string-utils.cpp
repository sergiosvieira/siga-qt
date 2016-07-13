#include "../../include/utils/string-utils.h"

#include "../../include/utils/md5.h"
#include "../../include/utils/util.h"
#include "../../include/utils/unaccent.h"

//#include "unicode/translit.h"
//#include "unicode/unistr.h"
//#include "unicode/calendar.h"
//#include "unicode/datefmt.h"


/** C++ **/
#include <cstring>
#include <sstream>
#include <numeric> // for std::accumulate
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <ctime>

//UnicodeString UNACCENT_RULES(
//	"[\\u00C0-\\u00C6] > A;"
//	"[\\u00C8-\\u00CB] > E;"
//	"[\\u00CC-\\u00CF] > I;"
//	"[\\u00D2-\\u00D8] > O;"
//	"[\\u00D9-\\u00DC] > U;"
//	"[\\u00E0-\\u00E6] > a;"
//	"[\\u00E8-\\u00EB] > e;"
//	"[\\u00EC-\\u00EF] > i;"
//	"[\\u00F0-\\u00F8] > o;"
//	"[\\u00F9-\\u00FF] > u;"
//	"[\\u00E7] > c;"
//	"[\\u00C7] > C;"
//	);

//UnicodeString IMPORT_RULES(
//	"[\\u03B2] > á;"
//	"[\\u03D0] > á;"
//	"[\\u00DF] > á;"
//	"[\\u00B3] > ³;"
//	"[\\u00C2] > ;"
//	"[\\u00E7] > ç;"
//	"[\\u00E3] > ã;"
//	"Ã§ > ç;"
//	"Ã£ > ã;"
//    );

using namespace std;
using namespace SIGA::DS;

void StringUtils::trim(std::string& a_string)
{
	string::size_type pos = a_string.find_last_not_of(' ');

	if (pos != string::npos)
	{
		a_string.erase(pos + 1);
		pos = a_string.find_first_not_of(' ');

		if (pos != string::npos)
		{
			a_string.erase(0, pos);
		}
	}
	else
	{
		a_string.erase(a_string.begin(), a_string.end());
	}
}

void StringUtils::split(std::vector<std::string>& a_vector,
						const std::string& a_line,
						const std::string& a_delimiter)
{
	a_vector.clear();

	const char *delimiter = a_delimiter.c_str();
	char *cstr = const_cast<char*>(a_line.c_str());
	char *current_char = strtok(cstr, delimiter);

	while (current_char != NULL)
	{
		a_vector.push_back(string(current_char));
		current_char = strtok(NULL, delimiter);
	}
}

bool StringUtils::replace(string &a_string, 
						  const string &a_stringFrom, 
						  const string &a_stringTo)
{
	size_t current_pos = a_string.find(a_stringFrom);
	if (current_pos == std::string::npos)
	{
		return false;
	}
	std::string aux = a_string;
	size_t aux_pos = current_pos;
	while (current_pos != std::string::npos)
	{
		aux.replace(aux_pos, a_stringFrom.length(), a_stringTo);
		current_pos = a_string.find(a_stringFrom, current_pos + 1);
		aux_pos = aux.find(a_stringFrom, aux_pos + 1);
	}
	a_string = aux;
	return true;
}

void StringUtils::createsLayerName(std::string& a_layerName,
								   const std::string& a_inputName)
{
	std::string fullFilename = std::string(a_inputName);

	StringUtils::filename(a_layerName,
						  fullFilename);
	StringUtils::replace(a_layerName,
						 ".shp", 
						 "");

	a_layerName += "_layer";
}

void StringUtils::normalize(std::string& a_normalizedString,
							const std::string& a_string)
{
//	Transliterator * rbtUnaccent;
//	UParseError pError;
//	UErrorCode status = U_ZERO_ERROR;

//	rbtUnaccent = Transliterator::createFromRules("RBTUnaccent",
//												   UNACCENT_RULES,
//												   UTRANS_FORWARD,
//												   pError,
//												   status);
//	check(status, "Transliterator::createFromRules");

//	UnicodeString uString(a_string.c_str());

//	rbtUnaccent->transliterate(uString);

//	makeString(a_normalizedString, uString);
}

void StringUtils::extractFilename(std::string& a_filename,
								  const std::string& a_fullPath)
{
	filename(a_filename, a_fullPath);
	std::vector<std::string> splited;
	split(splited, a_filename, ".");
	if (splited.size() > 0)
	{
		a_filename = splited.at(0);
	}
}

void StringUtils::filename(std::string& a_filename,
						   const std::string& a_fullPath)
{
	std::vector<std::string> splited;
	std::string fullPath = a_fullPath;
	std::string token = "#";
	StringUtils::replace(fullPath, "\\", token);
	StringUtils::replace(fullPath, "\\\\", token);
	StringUtils::replace(fullPath, "/", token);
	StringUtils::split(splited, fullPath, token);
	if (fullPath.size() > 0)
	{
		a_filename = splited.back();
	}
}

void StringUtils::basename(std::string& a_basename,
						   const std::string& a_path)
{
	std::string path = std::string(a_path);
	bool found = StringUtils::replace(path, "\\", "#");
	
	found |= StringUtils::replace(path, "\\\\", "#");
	found |= StringUtils::replace(path, "/", "#");

	std::vector<std::string> array;

	StringUtils::split(array,
					   a_path,
					   ".");

	std::string splited = array.front();

	if (found == true)
	{
		std::vector<std::string> vector;
		StringUtils::split(vector,
						   splited, 
						   "#");

		a_basename.clear();
		a_basename += vector.back();
	}
}

void StringUtils::path(std::string& a_path,
					   const std::string& a_fullPath)
{
	std::string kPathSeparator =
	#ifdef _WIN32
								"\\";
	#else
								"/";
	#endif
	std::vector<std::string> splittedPoint;
	StringUtils::split(splittedPoint, 
					   a_fullPath,
					   ".");

	if (splittedPoint.size() == 2)
	{
		StringUtils::split(splittedPoint,
						   a_fullPath,
						   kPathSeparator);
		splittedPoint.pop_back();
	}

	StringUtils::join(a_path,
					  splittedPoint, 
					  kPathSeparator);
}

void StringUtils::join(std::string& a_joinnedText,
					   std::vector<std::string>& a_vector,
					   const std::string& a_delimiter)
{
	if (a_delimiter.size() > 0 &&
		a_vector.size() > 0)
	{
		a_joinnedText.clear();
		a_joinnedText.reserve(a_vector.size() + (a_vector.size() * a_delimiter.size()) - 1);

		struct adder {
			std::string m_Joiner;
			adder(const std::string& s) : m_Joiner(s)
			{
			}
			std::string operator()(std::string&l, const std::string &r) 
			{
				l += r;
				l += m_Joiner;
				
				return l;
			}
		} adr(a_delimiter);

		std::string result = std::accumulate(a_vector.begin(), a_vector.end() - 1, a_joinnedText, adr);

		result += a_vector.back();
		a_joinnedText = result;
	}
}

void StringUtils::concat(std::string& a_output,
						 const std::string& a_first,
						 const std::string a_second)
{
	a_output.clear();
	a_output += a_first;
	a_output += a_second;
}

void StringUtils::removeUnspecifiedChars(std::string& a_resultText,
										 const std::string& a_text)
{
//	Transliterator * rbtUnaccent;
//	UParseError pError;
//	UErrorCode status = U_ZERO_ERROR;

//	rbtUnaccent = Transliterator::createFromRules(	"RBTUnaccent",
//													IMPORT_RULES,
//													UTRANS_FORWARD,
//													pError,
//													status);
//	check(status, "Transliterator::createFromRules");

//	UnicodeString uString(a_text.c_str());

//	rbtUnaccent->transliterate(uString);

//	a_resultText.clear();
//	makeString(a_resultText,
//			   uString);
}

void StringUtils::debugJSON(Json::Value a_value)
{
//	std::stringstream ss;

//	ss << a_value;
}

float StringUtils::strToFloat(std::string& strValue,
                              ConvertStringErrorCode& errorCode)
{
    StringUtils::replace(strValue, ",", ".");
//	return ConvertString<float>(a_stringValue, a_errorCode);
    char * pEnd = NULL;
    double d = strtod(strValue.c_str(), &pEnd);
    if (*pEnd)
    {
        errorCode = CS_ERROR_ON_CONVERT;
    }
    return d;
}

int StringUtils::strToInt(const std::string& strValue,
                          ConvertStringErrorCode& errorCode)
{

//	return ConvertString<int>(a_stringValue, a_errorCode);
    char * pEnd = NULL;
    long result = strtol(strValue.c_str(), &pEnd, 10);
    if (*pEnd)
    {
        errorCode = CS_ERROR_ON_CONVERT;
    }
    return result;
}

int StringUtils::isInteger(const std::string & a_string)
{
	bool result = true;
	std::istringstream iss(a_string);
	int integer;
	iss >> noskipws >> integer;
	result = iss.eof() && !iss.fail();
	return result;
}

int StringUtils::isFloat(const std::string & a_string)
{
	bool result = true;
	double d = std::strtod(a_string.c_str(), nullptr);
    result = (d > 0 && (d > std::numeric_limits<double>::max() || d < std::numeric_limits<double>::min()))
             || (d < 0 && (d < -std::numeric_limits<double>::max() || d > -std::numeric_limits<double>::min()));
	return !result;
}


std::string StringUtils::randomFilename(const std::string& a_filename,
										const std::string a_extension)
{
	std::string result = "";
	std::string md5String = "";
	md5(md5String, StringUtils::currentDateTime());
	result = "/" + a_filename + "_";
	result += md5String;
	result += "." + a_extension;
	return result;
}

std::string StringUtils::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
