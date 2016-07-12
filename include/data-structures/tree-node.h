#ifndef __TREE_NODE__
#define __TREE_NODE__

/** STL **/
#include <vector>

#include "sparse-matrix.h"

using namespace std;
using namespace SIGA::DS;

namespace SIGA
{
    namespace DS
    {
        /*!
         * \brief The TreeNode class
         */
        class TreeNode
        {
        public:
            TreeNode();
            /*!
             * \brief Default constructor with label
             * \param label
             */
            TreeNode(int label);
            /*!
             * \brief Get node value
             * \param row
             * \param col
             * \param a_value
             */
            void setValue(long row,
                          long col,
                          float value);
            /*!
             * \brief Returns current value of specified row, col
             * \param row
             * \param col
             * \return Float (When it not exists it returns -999.f)
             */
            float value(long row,
                        long col);
            /*!
             * \brief Sum value of (row, col) with passed value
             * \param row
             * \param col
             * \param value
             */
            void sum(long row,
                     long col,
                     float value);
            /*!
             * \brief Checks if specified value of (row, col) is empty
             * \param row
             * \param col
             * \return
             */
            bool isEmpty(long row,
                         long col);
            /*!
             * \brief Returns size of the sparse matrix of the Tree node
             * \return Integer Value
             */
            int size();
            /*!
             * \brief Label of Node
             * \return Integer Value
             */
            int label() const;
            /** Overloading Operators **/
            bool operator==(const TreeNode& other) const
            {
                return this == &other;
            }
            bool operator <(const TreeNode& other) const
            {
                return m_label < other.m_label;
            }
        protected:
            int m_label = 0;
            SparseMatrix<float> m_matrix;
        };
        /** find label **/
        struct find_label : std::unary_function<TreeNode, bool>
        {
            int m_label;
            find_label(int label): m_label(label){};
            bool operator()(TreeNode const& treeNode) const
            {
                return treeNode.label() == m_label;
            }
        };
    }
}

#endif // __TREE_NODE__
