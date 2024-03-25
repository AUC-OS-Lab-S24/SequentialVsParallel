
#include "test_fix_nproc.h"
#include "test_fix_N.h"

int main(){
  // test_fix_nproc("fixed_nproc/", multiply, 1000000, "res_fixed_nproc1.txt");
  // test_fix_nproc("fixed_nproc/", multiply, 1000000, "res_fixed_nproc2.txt");
  // test_fix_nproc("fixed_nproc/", multiply, 1000000, "res_fixed_nproc3.txt");

  test_fix_N("fix_n_res1", multiply, 20, "res_fixed_n1.txt");
  test_fix_N("fix_n_res2", multiply, 20, "res_fixed_n2.txt");
  test_fix_N("fix_n_res3", multiply, 20, "res_fixed_n3.txt");

  return 0;
}