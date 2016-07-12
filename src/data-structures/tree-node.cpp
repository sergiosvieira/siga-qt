#include "../../include/data-structures/tree-node.h"

using namespace SIGA::DS;


TreeNode::TreeNode(): m_label(0)
{
}

TreeNode::TreeNode(int label): m_label(label)
{

}

void TreeNode::setValue(long row,
                        long col,
                        float value)
{
    m_matrix[row][col] = value;
}

float TreeNode::value(long row,
                      long col)
{
    return isEmpty(row, col) ? -999.f : m_matrix[row][col];
}

void TreeNode::sum(long row,
                   long col,
                   float value)
{
    if (!isEmpty(row, col))
    {
        m_matrix[row][col] += value;
    }
    else
    {
        m_matrix[row][col] = value;
    }
}

bool TreeNode::isEmpty(long row,
                       long col)
{
    if (m_matrix.find(row) != m_matrix.end()
        && m_matrix[row].find(col) != m_matrix[row].end())
    {
        return false;
    }
    return true;
}

int TreeNode::size()
{
    return m_matrix.rows() * m_matrix.cols();
}

int TreeNode::label() const
{
    return m_label;
}
