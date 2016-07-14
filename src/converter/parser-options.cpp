#include "../../include/converter/parser-options.h"

using namespace SIGA;

vector<string> ParserOptions::commentsSymbol() const
{
    return m_commentsSymbol;
}

void ParserOptions::setCommentsSymbol(const vector<string> commentsSymbol)
{
    m_commentsSymbol = commentsSymbol;
}

int ParserOptions::skipLines() const
{
    return m_skipLines;
}

void ParserOptions::setSkipLines(int skipLines)
{
    m_skipLines = skipLines;
}

string ParserOptions::textDelimiter() const
{
    return m_textDelimiter;
}

void ParserOptions::setTextDelimiter(const string &textDelimiter)
{
    m_textDelimiter = textDelimiter;
}

string ParserOptions::fieldSeparator() const
{
    return m_fieldSeparator;
}

void ParserOptions::setFieldSeparator(const string &fieldSeparator)
{
    m_fieldSeparator = fieldSeparator;
}
