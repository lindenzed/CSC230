#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void readGrid( int rows, int cols, int grid[ rows ][ cols ] )
{
  // Add code to read in all the elements of grid from standard input.
    int i;
    int j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

// Add parameters to to pass a variable-sized array to the following
// function.  It's the same as the previous function, but I want you
// to get a chance to type it in yourself.
void reportMaxima( int rows, int cols, int grid [ rows ][ cols ] )
{
  // Add code to find local maxima and print them out in row major order.
    int i;
    int j;
    int temp;
    for ( i = 0; i < rows; i++ ) {
        for ( j = 0; j < cols; j++) {
            temp = grid[i][j];
            if ( i == 0 ) {
                if ( j == 0 ) {
                    if ( temp > grid[i][j + 1] && temp > grid[i + 1][j + 1] && temp > grid[i + 1][j] ) {
                        printf("%d %d\n", i, j);
                        continue;
                    }
                }
                if ( (j == cols - 1) ) {
                    if ( temp > grid[i][j - 1] && temp > grid[i + 1][j - 1] && temp > grid[i + 1][j] ) {
                        printf("%d %d\n", i, j);
                        continue;
                    }
                }
                if ( temp > grid[i][j - 1] && temp > grid[i + 1][j - 1] && 
                    temp > grid[i + 1][j] && temp > grid[i + 1][j + 1] && temp > grid[i][j + 1] ) {
                    printf("%d %d\n", i, j);
                    continue;
                }
            }
            if ( j == 0 ) {
                if ( i != 0 ) {
                    if ( temp > grid[i - 1][j] && temp > grid[i - 1][j + 1] && temp > grid[i][j + 1] && 
                        temp > grid[i + 1][j + 1] && temp > grid[i + 1][j] ) {
                        printf("%d %d\n", i, j);
                        continue;
                    }
                }
                if ( (i == rows - 1) ) {
                    if ( temp > grid[i][j + 1] && temp > grid[i - 1][j + 1] && temp > grid[i - 1][j] ) {
                        printf("%d %d\n", i, j);
                        continue;
                    }
                }
            }
            if ( (j == cols - 1) ) {
                if ( i == rows - 1) {
                    if (temp > grid[i][j - 1] && temp > grid[i - 1][j - 1] && temp > grid [i - 1][j] ) {
                        printf("%d %d\n", i, j);
                        continue;
                    }
                }
                else {
                    if ( i != 0 ) {
                        if ( temp > grid[i - 1][j] && temp > grid[i - 1][j - 1] && temp > grid[i][j - 1] && 
                            temp > grid[i + 1][j - 1] && temp > grid[i + 1][j] ) {
                            printf("%d %d\n", i, j);
                            continue;
                        }
                    }
                }
            }
            if (temp > grid[i - 1][j - 1] && temp > grid[i - 1][j] && temp > grid[i - 1][j +1] && 
                temp > grid[i][j - 1] && temp > grid[i][j + 1] && temp > grid[i + 1][j - 1] && 
                temp > grid[i + 1][j] && temp > grid[i + 1][j + 1] ) {
                printf("%d %d\n", i, j);
                continue;
            }
        }
    }
}

int main()
{
    int rows;
    int cols;
  // Add code to read in the grid size from standard input.
    scanf("%d", &rows);
    scanf("%d", &cols);

  // Declare a variable-sized array to hold the grid.
    int grid [ rows ][ cols ];

  // Call readGrid() to populate the array.
    readGrid(rows, cols, grid);
  
  // Call reportMaxima() to print out all local maxima.
    reportMaxima(rows, cols, grid);
  
  return EXIT_SUCCESS;
}
