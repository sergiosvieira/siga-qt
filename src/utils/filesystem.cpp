#include "../../include/utils/filesystem.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <direct.h>
//#include <SIGA/dirent.h>
#include <sstream>
#include <fstream>
#include <cassert>
#ifndef __GNUC__
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

using namespace std;


unsigned int CountLines( const vector <char> & buff, int sz ) 
{
    int newlines = 0;
    const char * p = &buff[0];

    for ( int i = 0; i < sz; i++ ) 
	{
    	if ( p[i] == '\n' ) 
		{
    		newlines++;
    	}
    }
    return newlines;
}

unsigned int FileRead( istream & is, vector <char> & buff ) 
{
    is.read( &buff[0], buff.size() );

    return is.gcount();
}

bool FileSystem::fileExists(const string &filename)
{
    ifstream file(filename);
    return file.is_open();
}

bool FileSystem::isDirectory(const string &path)
{
    if (path[path.size()] == '.')
    {
        return true;
    }
    for (int i = path.size(); i >= 0; i--)
    {
        if (path[i] == '.')
        {
            return false; // if we first encounter a . then it's a file
        }
        else if (path[i] == '\\' || path[i] == '/')
        {
            return true; // if we first encounter a \ it's a dir
        }
    }
}

bool FileSystem::removeDirectory(const string &path)
{
    // first off, we need to create a pointer to a directory
//    string aux = path;
//    if (path[path.length() - 1] != '\\')
//    {
//        aux += "\\";
//    }

//    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!

//    pdir = opendir(path.c_str());

//    struct dirent *pent = NULL;

//    if (pdir == NULL)
//    { // if pdir wasn't initialised correctly
//        return false; // return false to say "we couldn't do it"
//    } // end if

//    char file[256];
//    int counter = 1; // use this to skip the first TWO which cause an infinite loop (and eventually, stack overflow)

//    while (pent = readdir(pdir))
//    { // while there is still something in the directory to list
//        if (counter > 2)
//        {
//            for (int i = 0; i < 256; i++)
//            {
//                file[i] = '\0';
//            }

//            strcat(file, path.c_str());

//            if (pent == NULL)
//            { // if pent has not been initialised correctly
//                return false; // we couldn't do it
//            } // otherwise, it was initialised correctly, so let's delete the file~

//            strcat(file, pent->d_name); // concatenate the strings to get the complete path

//            if (isDirectory(file) == true)
//            {
//                removeDirectory(file);
//            }
//            else
//            { // it's a file, we can use remove
//                remove(file);
//            }
//        }
//        counter++;
//    }

//    // finally, let's clean up
//    closedir(pdir); // close the directory

//    if (!rmdir(path.c_str()))
//    {
//        return false; // delete the directory
//    }

    return true;
}

string FileSystem::currentPath(const string &filename)
{
    char cCurrentPath[FILENAME_MAX];
    GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

    std::string result;

    result += cCurrentPath;
    result += "\\";
    result += filename;
    result += "\0";

    return result;
}

bool FileSystem::concatFiles(const string &firstFile,
                             const string &secondFile,
                             const string &outputFilename)
{
    bool result = true;

    std::ifstream first(firstFile,
                        std::ios_base::binary);

    if (!first.is_open())
    {
        first.close();

        return false;
    }

    std::ifstream second(secondFile,
                         std::ios_base::binary);

    if (!second.is_open())
    {
        second.close();

        return false;
    }

    std::ofstream output(outputFilename,
                         std::ios_base::binary | std::ios_base::app);

    if (!output.is_open())
    {
        output.close();

        return false;
    }

    output << first.rdbuf() << second.rdbuf();
    first.close();
    second.close();
    output.close();

    return result;
}

unsigned int FileSystem::countLines(const string &filename)
{
    int result = 0;
    const int bufferSize = 1048576; // 1024 * 1024
    std::vector<char> buffer(bufferSize);
    std::ifstream ifs(filename);

    while (int bytesRead = FileRead(ifs, buffer) )
    {
        result += CountLines( buffer, bytesRead);
    }

    return result;
}
