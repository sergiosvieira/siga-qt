#ifndef __PARSER_OPTIONS__
#define __PARSER_OPTIONS__

#include <string>
#include <vector>

using namespace std;

namespace SIGA
{
    /*!
     * \brief The ParserOptions class
     */
    class ParserOptions
    {
    public:
        ParserOptions(){};
        /*!
         * \brief comments Symbol
         * \return
         */
        vector<string> commentsSymbol() const;
        /*!
         * \brief set Comments Symbol
         * \param commentsSymbol
         */
        void setCommentsSymbol(const vector<string> commentsSymbol);
        /*!
         * \brief skip Lines
         * \return
         */
        int skipLines() const;
        /*!
         * \brief set Skip Lines
         * \param skipLines
         */
        void setSkipLines(int skipLines);
        /*!
         * \brief text Delimiter
         * \return
         */
        string textDelimiter() const;
        /*!
         * \brief set Text Delimiter
         * \param textDelimiter
         */
        void setTextDelimiter(const string &textDelimiter);
        /*!
         * \brief field Separator
         * \return
         */
        string fieldSeparator() const;
        /*!
         * \brief set Field Separator
         * \param fieldSeparator
         */
        void setFieldSeparator(const string &fieldSeparator);
    protected:
        vector<string> m_commentsSymbol = vector<string>{"#"};
        string m_textDelimiter = "\"";
        string m_fieldSeparator = ",";
        int m_skipLines = 0;
    private:
    };
}

#endif // __PARSER_OPTIONS__
