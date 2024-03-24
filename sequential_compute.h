#include <stdio.h>
#include <stdlib.h>
//File should contain comma seperated numbers



int sequential_compute(const char *filepath, int (*f)(int, int))
{
    FILE *file = fopen(filepath, "r");

    if (!file)
    {
        printf("Couldn't open file\n");
        exit(-1);
    }

    int result, temp;

    fscanf(file, "%d", &result); 

    while (fscanf(file, ",%d", &temp) == 1)
    { 
        result = f(result, temp);
    }

    fclose(file);
    return result;
}

