
#ifndef TEST_FIX_NPROC_H
#define TEST_FIX_NPROC_H

#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"
//#include <time.h>

// I have 4 cores 
#define NUMBER_OF_PROCESSES 4

int test_fix_nproc(char *fileDirectory, int (*operation)(int, int), long N)
{
    char filepath[1024];

    // generate all files first
    for(long i = 1; i <= N; i++){
        sprintf(filepath, "%s%ld", fileDirectory, i);
        generate_n(filepath, i);
    }

    FILE *fix_nproc_res_file_seq = fopen("fix_nproc_res_seq.txt", "w"); 

    struct timespec start, end;
    for (long i = 1; i <= N; i++){
        sprintf(filepath, "%s%ld", fileDirectory, i);
        clock_gettime(CLOCK_MONOTONIC, &start);
        sequential_compute(filepath, operation);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fix_nproc_res_file_seq, "%f,",time_taken);
        fflush(fix_nproc_res_file_seq);
    }
    fclose(fix_nproc_res_file_seq);

    
    FILE *fix_nproc_res_file_par = fopen("fix_nproc_res_par.txt", "w"); 
    for (long i = 1; i <= N; i++){
        sprintf(filepath, "%s%ld", fileDirectory, i);
        clock_gettime(CLOCK_MONOTONIC, &start);
        parallel_compute(filepath, NUMBER_OF_PROCESSES, operation);
        clock_gettime(CLOCK_MONOTONIC, &end);

        //double time_taken = ((double) par_end_time - par_start_time) / CLOCKS_PER_SEC;
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fix_nproc_res_file_par, "%f,",time_taken);
        fflush(fix_nproc_res_file_par);
    }
    fclose(fix_nproc_res_file_par);

    return 0;
}




#endif