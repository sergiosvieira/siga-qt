#ifndef __FILE_SYSTEM__
#define __FILE_SYSTEM__

#include <iostream>

using namespace std;

/*!
 * \brief The FileSystem class
 */
class FileSystem
{
public:
    /*!
     * \brief check if file exists
     * \param filename
     * \return
     */
    static bool fileExists(const string& filename);
    /*!
     * \brief check if path points to some directory
     * \param path
     * \return
     */
    static bool isDirectory(const string& path);
    /*!
     * \brief remove directory
     * \param path
     * \return
     */
    static bool removeDirectory(const std::string& path);
    /*!
     * \brief return current path
     * \param filename
     * \return
     */
    static std::string currentPath(const string& filename);
    /*!
     * \brief concat two file and save the result to other file
     * \param firstFile
     * \param secondFile
     * \param outputFilename
     * \return
     */
    static bool concatFiles(const string& firstFile,
                            const string& secondFile,
                            const string& outputFilename);
    /*!
     * \brief count lines of a file
     * \param filename
     * \return
     */
    static unsigned int countLines(const string& filename);
};

#endif /* __FILE_SYSTEM__ */
