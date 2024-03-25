
#ifndef TEST_FIX_NPROC_H
#define TEST_FIX_NPROC_H

#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"

// I have 4 cores  - 2
#define NUMBER_OF_PROCESSES 2

int test_fix_nproc(char *fileDirectory, int (*operation)(int, int), long N, char* res_file_path)
{
    char filepath[1024];

    // generate all files first
    for(long i = 1; i <= N; i = i + 1000){
        sprintf(filepath, "%s%ld", fileDirectory, i);
        generate_n(filepath, i);
    }

    FILE *fix_nproc_res_file = fopen(res_file_path, "w"); 

    struct timespec start_seq, end_seq;
    struct timespec start_par, end_par;
    for (long i = 1; i <= N; i= i + 1000){
        sprintf(filepath, "%s%ld", fileDirectory, i);

        //sequential profiling
        clock_gettime(CLOCK_MONOTONIC, &start_seq);
        sequential_compute(filepath, operation);
        clock_gettime(CLOCK_MONOTONIC, &end_seq);

        double time_taken_seq = (end_seq.tv_sec - start_seq.tv_sec) + (end_seq.tv_nsec - start_seq.tv_nsec) / 1e9;

        //parallel profiling
        clock_gettime(CLOCK_MONOTONIC, &start_par);
        parallel_compute(filepath, NUMBER_OF_PROCESSES, operation);
        clock_gettime(CLOCK_MONOTONIC, &end_par);

        double time_taken_par = (end_par.tv_sec - start_par.tv_sec) + (end_par.tv_nsec - start_par.tv_nsec) / 1e9;
        fprintf(fix_nproc_res_file, "%ld,%f,%f\n", i, time_taken_par, time_taken_seq);
        fflush(fix_nproc_res_file);
    }

    fclose(fix_nproc_res_file);

    return 0;
}




#endif