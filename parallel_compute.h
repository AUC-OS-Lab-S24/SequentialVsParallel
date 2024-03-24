// takes path of file containing N numbers seprated by commas
// takes number of processes
// takes a function pointer that takes 2 int and returns int
// splits the numbers into N/p parts and distributes to p processes
// returns the result of the function on the numbers

#ifndef PARALLEL_COMPUTE_H
#define PARALLEL_COMPUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int parallel_compute(char *path, int n_proc, int (*f)(int, int)){
    // open file
    FILE *file = fopen(path, "r");
    if(!file){
        printf("Error opening file\n");
        return -1;
    }

    // read numbers until file is empty
    int temp, count = 0;
    while (fscanf(file, ",%d", &temp) == 1)
    { 
        count++;
    }
    fseek(file, 0, SEEK_SET);

    // read numbers into array
    int *numbers = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
    {
        fscanf(file, ",%d", &numbers[i]);
    }
    fclose(file);

    // split numbers into n_proc parts
    // assign a starting index to each process
    int *parts = (int *)malloc(n_proc * sizeof(int));
    // size will be equal to count/n_proc, unless count is not divisible by n_proc


    int size = count / n_proc;
    int parts = size;
    // check if count is divisible by n_proc
    if(count % n_proc != 0){
        parts++;
    }
    // assign part index and size
    for (int i = 0; i < n_proc; i++)
    {
        parts[i] = i * size;
    }
    int lastSize = count - (n_proc - 1) * size;

    // create n_proc processes
    // each process will compute the function on its part of the numbers
    // and return the result
    int *results = (int *)malloc(n_proc * sizeof(int));
    
    int forkID = fork();

    


    
}

#endif