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
#include <sys/wait.h>

int parallel_compute(char *path, int n, int *numbers,  int n_proc, int (*f)(int, int)){
    // open file
    FILE *file = fopen(path, "r");
    if(!file){
        printf("Error opening file\n");
        return -1;
    }

    // read numbers until file is empty
    /*int temp, count = 1;
    fscanf(file, "%d", &temp); 

    while (fscanf(file, ",%d", &temp) == 1)
    { 
        count++;
    }
    // move file pointer to start
    fseek(file, 0, SEEK_SET);*/

    // read numbers into array

    // split numbers into n_proc parts

    // size will be equal to count/n_proc, unless count is not divisible by n_proc
    // in this case final process will have the remaining numbers


    int size = n / n_proc;

    // case where count is less than n_proc
    if(size == 0){
        size = 1;
        n_proc = n;
    }
   

    // create n_proc processes
    // each process will compute the function on its part of the numbers
    // and return the result
    int *results = (int *)malloc(n_proc * sizeof(int));
    
    // create a pipe for each process
    int **pipes = (int **)malloc(n_proc * sizeof(int *));
    for (int i = 0; i < n_proc; i++)
    {
        pipes[i] = (int *)malloc(2 * sizeof(int));
        pipe(pipes[i]);
        // test if pipe was created successfully
        if(pipes[i][0] == -1 || pipes[i][1] == -1){
            printf("Error creating pipe\n");
            return -1;
        }
    }



    for(int i = 0; i < n_proc; i++){
        pid_t pid = fork();
        if(pid == 0){
            // close pipe read end
            close(pipes[i][0]);
            // child process
            int start = i * size;
            // last index for last process is count - 1
            int end = (i == (n_proc - 1) )? n : (start + size);
            int result = numbers[start];
            for (int j = start + 1; j < end; j++)
            {
                result = f(result, numbers[j]);
            }
            
            // pass value to parent using pipe
            write(pipes[i][1], &result, sizeof(int));
            // close pipe write end
            close(pipes[i][1]);
            // exit child process
            exit(0);

        }else{
            // close pipe write end
            close(pipes[i][1]);
        }
    
    }

    // wait for all child processes to finish
    while(1){
        pid_t child = wait(NULL);
        if(child == -1){
            break;
        }
    }

    // read results from pipes
    for (int i = 0; i < n_proc; i++)
    {
        read(pipes[i][0], &results[i], sizeof(int));
        close(pipes[i][0]);
    }

    // combine results
    int finalResult = results[0];
    for (int i = 1; i < n_proc; i++)
    {
        finalResult = f(finalResult, results[i]);
    }

    // free memory
    free(results);
    for (int i = 0; i < n_proc; i++)
    {
        free(pipes[i]);
    }
    free(pipes);

    return finalResult; 

}
#endif