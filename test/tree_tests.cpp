#include <igloo/igloo_alt.h>
#include "../../include/data-structures/node.h"
#include "../../include/data-structures/tree.h"

using namespace igloo;
using namespace SIGA::DS;

Describe (NodeClassTests)
{
  It(TestNodeLinkages)
  {
      /*
       *      (1)
       *      /
       *    (2)-----(3)-(4)
       *
       */
      Node node1(1);
      Assert::That(node1.parent() == nullptr, Equals(true));
      Node node2(2, &node1);
      Assert::That(node1.child() != nullptr, Equals(true));
      Assert::That(node1.child()->label(), Equals(2));
      Assert::That(node2.parent() != nullptr, Equals(true));
      Assert::That(node2.parent()->label(), Equals(1));
      Assert::That(node2.child() == nullptr, Equals(true));
      Node node3(3, &node1);
      Assert::That(node2.next() != nullptr, Equals(true));
      Assert::That(node2.next()->label(), Equals(3));
      Assert::That(node3.previous() != nullptr, Equals(true));
      Assert::That(node3.previous()->label(), Equals(2));
      Node node4(4, &node1);
      Assert::That(node3.next() != nullptr, Equals(true));
      Assert::That(node3.next()->label(), Equals(4));
      Assert::That(node4.previous() != nullptr, Equals(true));
      Assert::That(node4.previous()->label(), Equals(3));
    }
};

Describe(TreeClassTest)
{
    It(TestFindLabel)
    {

    }
};

int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
