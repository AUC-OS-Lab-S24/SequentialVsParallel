#ifndef GENERATE_N_H
#define GENERATE_N_H

#include <stdio.h>
#include <time.h>

unsigned long RAND_A = 16807;
unsigned long RAND_MODULUS = 2147483647;

// rudimentary random number generator
long rand(seed){
    seed = (RAND_A * seed) % RAND_MODULUS;
    return seed;
}

// generate a file with n numbers
int generate_n(char* filepath, long n){
    
    FILE *file = fopen(filepath, "w");
    
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    time_t current_time = time(NULL);

    stdout = file;
    long random_number = (long)current_time; //as seed
    for(long i = 0; i < n; i++){
        random_number = rand(random_number);
        if(i == n - 1) {
            printf("%d",random_number);
            break;
        }

        printf("%d,",random_number); 
    }

    fclose(file);
    stdout = 0;
    return 0;
}

#endif