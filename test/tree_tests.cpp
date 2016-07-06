#include <igloo/igloo_alt.h>
#include "../../include/data-structures/node.h"
#include "../../include/data-structures/tree.h"

using namespace std;
using namespace igloo;
using namespace SIGA::DS;

#define __DEBUG__

Describe (TreeClassTests)
{
  It(TestNodeLinkages)
  {
      /*
       *      (1)
       *      /
       *    (2)-----(3)-(4)
       *
       */
      Tree t;
      shared_ptr<Node> node1 = t.add(1);
      shared_ptr<Node> node2 = t.add(2, node1);
      Assert::That(node1->child() != nullptr, Equals(true));
      shared_ptr<Node> node3 = t.add(3, node2);
      //Assert::That(node2->next() != nullptr, Equals(true));
      //Assert::That(node2->next()->label(), Equals(3));
      //shared_ptr<Node> node4 = t.add(4, node2);
      //cout << "--> " << node2->parent()->label() << "\n";
    }
};


int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
