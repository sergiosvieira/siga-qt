#include <igloo/igloo_alt.h>
#include <data-structures/sparse-matrix.h>

using namespace std;
using namespace igloo;
using namespace SIGA::DS;


Describe (SparseMatrixTest)
{
  It(SparseMatrixMustReturnCorrectSize)
  {
      /*!
       *    |0|1|2|
       *    -------
       * 0->|1| | |
       * 1->| | |2|
       */
      SparseMatrix<int> sm;
      sm[0][0] = 1;
      sm[1][2] = 2;
      Assert::That(sm.cols(), Equals(3));
      Assert::That(sm.rows(), Equals(2));
  }
  It(SparseMatrixMustReturnCorrectValue)
  {
      /*!
       *    |0|1|
       *    -----
       * 0->| |9|
       * 1->| |5|
       */
      SparseMatrix<int> sm;
      sm[0][1] = 9;
      sm[1][1] = 5;
      Assert::That(sm[0][1], Equals(9));
      Assert::That(sm[1][1], Equals(5));
  }
};


int main(int argc, char** argv)
{
    return TestRunner::RunAllTests(argc, argv);
}
