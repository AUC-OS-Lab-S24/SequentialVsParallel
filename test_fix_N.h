
#ifndef TEST_FIX_N_H
#define TEST_FIX_N_H

#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"

#define FIXED_N 1000


int text_fix_N(char *filepath, int (*operation)(int, int), int nproc){

    generate_n(filepath, FIXED_N);

    struct timespec start, end;

    FILE *fix_n_res_file_seq = fopen("fix_n_res_seq.txt", "w"); 

    clock_gettime(CLOCK_MONOTONIC, &start);
    sequential_compute(filepath, operation);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(fix_n_res_file_seq, "%f\n",time_taken);

    fflush(fix_n_res_file_seq);
    fclose(fix_n_res_file_seq);

    FILE *fix_n_res_file_par = fopen("fix_n_res_par.txt", "w"); 

    for(int i = 1; i <= nproc; i++){ 
        clock_gettime(CLOCK_MONOTONIC, &start);
        parallel_compute(filepath, i, operation);
        clock_gettime(CLOCK_MONOTONIC, &end);

        time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fix_n_res_file_seq, "%f\n" ,time_taken);
    }

    fflush(fix_n_res_file_par);
    fclose(fix_n_res_file_par);



    return 0;
}

#endif