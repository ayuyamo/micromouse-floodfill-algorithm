#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int maze[12][12];
    // Set all values to 111 using nested loops
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            maze[i][j] = 111; // Set each element to 111
        }
    }

    printf("Before memset:\n");
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 12; i++)
    {
        memset(maze[i], 0, 12 * sizeof(int));
    }
    printf("After memset: \n");
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}