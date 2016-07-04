#ifndef __TREE__
#define __TREE__

/** Data Structures **/
#include "node.h"


/*!
 * SIGA Namespace
 */
namespace SIGA
{
    /*!
     * Data Structure Namespace
     */
    namespace DS
    {
        /*!
         * \brief The Tree class
         * Store nodes from time serie/matrix values
         */
        class Tree
        {
        public:
        protected:
            Node* m_root = nullptr;
        };
    }
}

#endif // __TREE__
