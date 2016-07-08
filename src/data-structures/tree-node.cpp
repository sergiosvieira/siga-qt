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
                     shared_ptr<float> value)
{
    m_matrix[row][col] = value;
}

float TreeNode::value(long row,
                      long col)
{
    shared_ptr<float> sp(m_matrix[row][col]);
    float *value = sp.get();
    return value == nullptr ? -999 : *value;
}

void TreeNode::sum(long row,
                   long col,
                   float value)
{
    if (!isEmpty(row, col))
    {
        *m_matrix[row][col] += value;
    }
    else
    {
        m_matrix[row][col] = make_shared<float>(value);
    }
}

bool TreeNode::isEmpty(long row,
                       long col)
{
    shared_ptr<float> sp(m_matrix[row][col]);
    float *value = sp.get();
    return value == nullptr;
}

int TreeNode::size()
{
    return m_matrix.rows() * m_matrix.cols();
}

int TreeNode::label() const
{
    return m_label;
}

void TreeNode::destroyValues()
{
    for (auto matrixKeyValue: m_matrix)
    {
        std::map<long, shared_ptr<float>> mapped = matrixKeyValue.second;
        for (auto mapKeyValue: mapped)
        {
            mapKeyValue.second = nullptr;
        }
    }
}
