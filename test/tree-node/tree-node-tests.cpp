#include "data-structures/tree-node.h"
#include <igloo/igloo_alt.h>


using namespace std;
using namespace igloo;
using namespace SIGA::DS;


Describe (TreeNodeTest)
{
    It(TestSetAndGetValues)
    {
      TreeNode node(1);
      Assert::That(node.value(0, 0), Equals(-999.f));// No value defined
      node.setValue(0, 0, 100.f);
      Assert::That(node.label(), Equals(1));
      Assert::That(node.value(0, 0), Equals(100.f));
    }
    It(TestArithmeticOperation)
    {
      TreeNode node(1);
      node.setValue(0, 0, 1.f);
      node.sum(0, 0, 1.f);
      Assert::That(node.value(0, 0), Equals(2.f));
    }
    It(TestWhenNodeIsEmpty)
    {
      TreeNode node(1);
      Assert::That(node.isEmpty(0, 0), Equals(true));
      node.setValue(0, 0, 1.f);
      Assert::That(node.isEmpty(0, 0), Equals(false));
    }
    It(TestNodeValuesSize)
    {
      TreeNode node(1);
      Assert::That(node.size(), Equals(0));
      node.setValue(0, 0, 1.f);
      node.setValue(1, 2, 2.f);
      Assert::That(node.size(), Equals(6));
    }
    It(TestOperatorOverloading)
    {
        TreeNode node1(1);
        TreeNode node2(1);
        TreeNode node3(2);
        Assert::That(node1 == node2, Equals(false));
        Assert::That(node1 == node1, Equals(true));
        Assert::That(node1 < node3, Equals(true));
    }
};


int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
