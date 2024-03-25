
#include "test_fix_nproc.h"
#include "test_fix_N.h"

int main(){
  test_fix_nproc("fixed_nproc/", multiply, 1000000, "res_fixed_nproc1.txt");
  test_fix_nproc("fixed_nproc/", multiply, 1000000, "res_fixed_nproc2.txt");
  test_fix_nproc("fixed_nproc/", multiply, 1000000, "res_fixed_nproc3.txt");

  test_fix_N("fix_n_res1", multiply, 10, "res_fixed_n.txt");
  test_fix_N("fix_n_res2", multiply, 10, "res_fixed_n.txt");
  test_fix_N("fix_n_res3", multiply, 10, "res_fixed_n.txt");



  return 0;
}