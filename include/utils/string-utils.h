#ifndef __STRING_UTILS__
#define __STRING_UTILS__

/** C++ **/
#include <string>

/** STL **/
#include <vector>

/** Extends **/
#include "../lib/json/include/json/json.h"

#include "../converter/convert-string-template.h"

namespace SIGA
{
    namespace DS
    {
        class StringUtils
        {
        private:

        public:
            /*!
            * brief remove left and right white spaces
            */
            static void trim(std::string& a_string);
            /**
            * @brief split
            * @param std::vector<std::string>& - Result vector
            * @param const std::string& - Input string line
            * @param const std::string& - Delimiter
            * @return
            */
            static void split(std::vector<std::string>& a_vector,
                              const std::string& a_line,
                              const std::string& a_delimiter);
            /**
            * @brief replace
            * @param a_string
            * @param a_stringFrom
            * @param a_stringTo
            * @return
            */
            static bool replace(std::string& a_string, const std::string& a_stringFrom, const std::string& a_stringTo);
            /**
            * @brief createsLayerName
            * @param std::string& - Layer name result
            * @param const std::string& - Input name
            */
            static void createsLayerName(std::string& a_layerName,
                                         const std::string& a_inputName);
            /**
             * @brief normalize input (remove unspecified characters)
             * @param std::string& - Normalized string result
             * @param const std::string& - Input string
             */
            static void normalize(std::string& a_normalizedString,
                                         const std::string& a_string);
            /**
             * @brief get only file name from a full path string without extension
             * @param std::string& - output file name
             * @param const std::string& - Input full path string
             */
            static void extractFilename(std::string& a_filename,
                                        const std::string& a_fullPath);
            /**
             * @brief get only file name from a full path string
             * @param std::string& - output file name
             * @param const std::string& - Input full path string
             */
            static void filename(std::string& a_filename,
                                 const std::string& a_fullPath);
            /**
             * @brief gets file name (without extension) from a file path
             * @param std::string& - Result basename
             * @param const std::string& - Input full path and filename
             */
            static void basename(std::string& a_basename,
                                 const std::string& a_path);
            /**
             * @brief remove file name from full path
             * @param std::string& - result string, only path
             * @param const std::string& -  full path (path + filename)
             */
            static void path(std::string& a_path,
                             const std::string& a_fullPath);
            /**
             * @brief join a vector of string
             */
            static void join(std::string& a_joinnedText,
                             std::vector<std::string>& a_vector,
                             const std::string& a_delimiter = ";");
            /**
             * @brief concat two strings
             * @param std::string& - Result string
             * @param const std::string& - First string
             * @param const std::string& - Second string
             */
            static void concat(std::string& a_output,
                               const std::string& a_first,
                               const std::string a_second);
            /**
             * @brief remove unspecified characters from string
             * @param std::string& - Result  text
             * @param const std::string& - Input text
             **/
            static void removeUnspecifiedChars(std::string& a_resultText,
                                               const std::string& a_text);
            /**
             * @brief print json string
             **/
            static void debugJSON(Json::Value a_json);
            /**
             * @brief convert string to float
             */
            static float strToFloat(std::string& strValue,
                                    ConvertStringErrorCode& errorCode);
            /**
             * @brief convert string to int
             */
            static int strToInt(const std::string& a_stringValue,
                                ConvertStringErrorCode& errorCode);
            /**
             * @brief checks if string is a integer value
             */
            static int isInteger(const std::string& a_string);
            /**
             * @brief checks if string is a integer value
             */
            static int isFloat(const std::string& a_string);
            static std::string randomFilename(const std::string& a_filename,
                                              const std::string a_extension);
            static std::string currentDateTime();
        };

    }
}

#endif /** __STRING_UTILS__ **/
