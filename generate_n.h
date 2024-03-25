#ifndef GENERATE_N_H
#define GENERATE_N_H

#include <stdio.h>
#include <time.h>

#define RAND_A 16807
#define RAND_MODULUS 2147483647

// operation
int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}


// rudimentary random number generator
long rud_rand(long seed){
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

    clock_t current_time = time(NULL);

    long random_number = (long)current_time; //as seed
    for(long i = 0; i < n; i++){
        random_number = rud_rand(random_number);
        if(i == n - 1) {
            fprintf(file, "%ld", random_number);
            break;
        }

        fprintf(file, "%ld,", random_number); 
    }

    fclose(file);
    return 0;
}

#endif