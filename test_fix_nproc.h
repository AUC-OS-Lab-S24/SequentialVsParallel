
#ifndef TEST_FIX_NPROC_H
#define TEST_FIX_NPROC_H

#include "parallel_compute.h"
#include "sequential_compute.h"
#include "generate_n.h"

// I have 16 cores  - 2
#define NUMBER_OF_PROCESSES 14

int test_fix_nproc(char *fileDirectory, int (*operation)(int, int), long N, char* res_file_path)
{
    char filepath[1024];

    // generate all files first
    for(long i = 16000000; i <= N; i = i + 10000){
        sprintf(filepath, "%s%ld", fileDirectory, i);
        generate_n(filepath, i);
    }

    FILE *fix_nproc_res_file = fopen(res_file_path, "w"); 

    struct timespec start_seq, end_seq;
    struct timespec start_par, end_par;

    double difference_sum_seq = 0;
    double difference_sum_par = 0;

    for (long i = 16000000; i <= N; i= i + 10000){
        sprintf(filepath, "%s%ld", fileDirectory, i);

        //sequential profiling
        for (int j = 0; j < 3; j++) {
            clock_gettime(CLOCK_MONOTONIC, &start_seq);
            sequential_compute(filepath, operation);
            clock_gettime(CLOCK_MONOTONIC, &end_seq);

            double time_taken_seq = (end_seq.tv_sec - start_seq.tv_sec) + (end_seq.tv_nsec - start_seq.tv_nsec) / 1e9;
            difference_sum_seq += time_taken_seq;
        }
        difference_sum_seq /= 3;

        //parallel profiling
        for (int j = 0; j < 3; j++) {
            clock_gettime(CLOCK_MONOTONIC, &start_par);
            parallel_compute(filepath,i, NUMBER_OF_PROCESSES, operation);
            clock_gettime(CLOCK_MONOTONIC, &end_par);

            double time_taken_par = (end_par.tv_sec - start_par.tv_sec) + (end_par.tv_nsec - start_par.tv_nsec) / 1e9;
            difference_sum_par += time_taken_par;
        }
        difference_sum_par /= 3;

        fprintf(fix_nproc_res_file, "%ld,%f,%f\n", i, difference_sum_par, difference_sum_seq);
        fflush(fix_nproc_res_file);
    }

    fclose(fix_nproc_res_file);

    return 0;
}




#endif