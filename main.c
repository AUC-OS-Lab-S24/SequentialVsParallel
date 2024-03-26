
#include "test_fix_nproc.h"
#include "test_fix_N.h"

int main(){
  //test_fix_nproc("fixed_nproc/", multiply, 2000000, "res_fixed_nproc.txt");
  test_fix_N("fix_n_res3", multiply, 32, "res_fixed_n.txt");
  return 0;
}