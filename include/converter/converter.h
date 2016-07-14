#ifndef __SIGA_CONVERTER__
#define __SIGA_CONVERTER__

#include <string>
#include "../../include/data-structures/tree.h"

#include "../../include/data-structures/tree-node.h"
#include "../../include/data-structures/tree.h"
#include "../../include/converter/converter-options.h"
#include "../../include/converter/parser-options.h"


namespace SIGA
{
    /*!
     * \brief The Converter class
     */
    class Converter
    {
    public:
        static tree<TreeNode> loadTree(const std::string& filename,
                                       const ParserOptions& parserOptions,
                                       const ConverterOptions& converterOptions);
        static void load(const char* filename,
                         const ParserOptions &options,
                         const ConverterOptions &cOptions);
    };

}


#endif /** __SIGA_CONVERTER__ **/
