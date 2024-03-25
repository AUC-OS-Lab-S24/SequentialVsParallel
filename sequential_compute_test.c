#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequential_compute.h"
#include "parallel_compute.h"
int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

int sequential_compute_test()
{
    
    // Allow choice of add or multiply
    while(1){

        char filepath[16] = "Tests/test";// modify filepath[10] to test different files

        int choice = 0;

        printf("Enter 1 for addition or 2 for multiplication or 3 to exit: ");
        scanf("%d", &choice);

        int (*operation)(int, int);

        if (choice == 1)
        {
            operation = add;
        }
        else if (choice == 2)
        {
            operation = multiply;
        }
        else if (choice == 3)
        {
            return 0;
        }
        else
        {
            printf("Invalid choice\n");
            return -1;
        }

        int fileNumber;
        printf("Enter test file number (1, 2, 3): ");
        scanf("%d", &fileNumber);

        strcat(filepath, (char[]){fileNumber + '0', '\0'});
        strcat(filepath, ".txt");


        int result = sequential_compute(filepath, operation);

        // result from parallel_compute
        int parallel_result = parallel_compute(filepath, 10, operation);

        printf("Result from sequential: %d\n", result);
        printf("Result from parallel: %d\n", parallel_result);
    }
}
