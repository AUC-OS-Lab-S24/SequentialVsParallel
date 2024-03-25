
#ifndef TEST_FIX_N_H
#define TEST_FIX_N_H

#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"

#define FIXED_N 1000


int test_fix_N(char *filepath, int (*operation)(int, int), int nproc, char* res_filepath){

    generate_n(filepath, FIXED_N);

    struct timespec start_seq, end_seq;
    struct timespec start_par, end_par;

    FILE *fix_n_res_file = fopen(res_filepath, "w"); 

    for(int i = 1; i <= nproc; i++){ 
        clock_gettime(CLOCK_MONOTONIC, &start_seq);
        sequential_compute(filepath, operation);
        clock_gettime(CLOCK_MONOTONIC, &end_seq);
        double time_taken_seq = (end_seq.tv_sec - start_seq.tv_sec) + (end_seq.tv_nsec - start_seq.tv_nsec) / 1e9;

        clock_gettime(CLOCK_MONOTONIC, &start_par);
        parallel_compute(filepath, i, operation);
        clock_gettime(CLOCK_MONOTONIC, &end_par);

        double time_taken_par = (end_par.tv_sec - start_par.tv_sec) + (end_par.tv_nsec - start_par.tv_nsec) / 1e9;
        fprintf(fix_n_res_file, "%ld,%f,%f\n", i, time_taken_par, time_taken_seq);
        fflush(fix_n_res_file);
    }

    fclose(fix_n_res_file);



    return 0;
}

#endif