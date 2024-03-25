
#include "test_fix_nproc.h"
#include "test_fix_N.h"

int main(){
  test_fix_nproc("fixed_nproc/", multiply, 100);
  //test_fix_nproc("fixed_nproc2/", multiply, 100);
  //test_fix_nproc("fixed_nproc3/", multiply, 100);

  //test_fix_n("fix_n_res1", multiply, 10);
  //test_fix_n("fix_n_res2", multiply, 10);
  //test_fix_n("fix_n_res3", multiply, 10);



  return 0;
}