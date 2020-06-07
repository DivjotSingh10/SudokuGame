#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ASSIGNMENT 1 for Data Structure and Algorithm Development C
 * Author: Divjot Chawla
 * Date: 3 June, 2020
 * Version: 1.6
 * Description: This is a Sudoku grid game which asks for user input and also validates the grid
 * Submitted to: Muhammad Mohiuddin
 */

#define TRUE 1
#define FALSE 0

/* Validation of entry-
 * will be valid only if there are 1 to 9
 */
int validEntry(int entry[9])
{
    int d,t,v;

    // This loop will find values from 1 to 9
    for(t=1; t<=9; t++)
    {
        v=FALSE;

        //Finding the next value
        for(d=0; d<9; d++){
            if(entry[d]== t)
            {
                v=TRUE;
                break;
            }
        }


        if(!v)  // This will stop if the next input value was not found
            return FALSE;
    }
    // This will be a valid entry if all values were found
    return TRUE;
}

/* Validation of the board- I will be using three validation, i.e,
 * 1. Validation of row- should contain 1 to 9 only, and no duplicates.
 * 2. Validation of column- should contain 1 to 9 only, and no duplicates.
 * 3. Validation by 3*3 matrix- should have unique values.
 */
int validGrid(int grid[9][9])
{
    int record[9];
    int q,w;
    int x,y,z;

    // Row validator
    for (q=0; q<9; q++) {

        // getting a row
        for (w = 0; w < 9; w++)
            record[w] = grid[q][w];

        // this will stop if invalid
        if (!validEntry(record))
            return FALSE;
    }

    // Column validator
    for(w=0; w<9; w++)
    {
        for (q=0; q<9; q++)
            record[q]=grid[q][w];

        if(!validEntry(record))
            return FALSE;
    }

    //3*3 matrix validator
    for (q=0; q<3; q+=3)
    {
        for (w=0; w<3; w+=3)
        {
            z=0;

            // getting a 3*3 matrix
            for (x=q; x<q+3; x++)
                for (y=w; y<w+3; y++)
                    record[z++]= grid[x][y];

            // this will stop if invalid
            if(!validEntry(record))
                return FALSE;
        }
    }
    return TRUE;
}

/* This will generate a random row with unique values from
 * the range of 1 to 9 only.
 */
void randomRow(int row[9])
{
    int x,y,z;

    // this will put the numbers in the row
    for(x=0; x < 9; x++)
        row[x]= x + 1;

    /* since we will be generating random rows seven times
     * after the user input, we need to make sure that every time the
     * row elements are shuffled
     */

    for (x=0; x < 9; x++)
    {
        y= rand() % 9;
        z= row[x];
        row[x]= row[y];
        row[y]= z;
    }
}

/* This will read the row and make sure that all the input numbers
 * are unique and belongs to the range of 1 to 9 only.
 */
void readerRow(int row[9])
{
    int i;

    while (TRUE)
    {
        for (i = 0; i < 9; i++)
            scanf("%d", &row[i]);

        if (validEntry(row))
            return;

        printf("Invalid input. Try again with exactly 9 unique numbers\n");
        printf("that belong to range of 1 to 9 only separated by a single space.\n");
        printf("\n");
    }
}


/* This will print the sudoku grid and check whether it is valid or invalid
 * based on row, column and 3*3 matrix validation
 */
void printGrid(int grid[9][9]){
    int row,col;

    /* Printing the sudoku grid*/
    printf("------------SUDOKU GRID------------\n");
    for (row=0; row<9; row++)
    {
        for (col=0; col<9; col++)
            printf("%4d", grid[row][col]);
        printf("\n");
    }
    printf("\n");

    // This will print the decision as to whether it is a valid or invalid solution
    if (validGrid(grid)) {
        printf("It is a VALID sudoku grid.\n");
        printf("\n");
    }
    else {
        printf("It is an INVALID soduko grid\n");
        printf("Better luck next time\n");
        printf("\n");
    }
}

/* This is the main function
 * a.k.a the entry in the program
 */
int main() {
    int row;
    int grid[9];
    int i;

    //provided values which will meet the validations and this is also the default grid
    int board[9][9]= {
            {5,3,4,6,7,8,9,1,2},
            {6,7,2,1,9,5,3,4,8},
            {1,9,8,3,4,2,5,6,7},
            {8,5,9,7,6,1,4,2,3},
            {4,2,6,8,5,3,7,9,1},
            {7,1,3,9,2,4,8,5,6},
            {9,6,1,5,3,7,2,8,4},
            {2,8,7,4,1,9,6,3,5},
            {3,4,5,2,8,6,1,7,9}
    };

    srand((unsigned)time(0));

    printGrid(board);

    for (row=0; row<2; row++){
        printf("Enter row %d of your Sudoku grid\n", row + 1);
        printf("Use Space/Tab/Return key to enter the next values\n");
        printf("and press 'Return' after entering nine integers.\n");
        printf("Remember, to make a valid row of Sudoku grid,\n");
        printf("all integers should be distinct and range from 1 to 9\n");
        printf("\n");
        readerRow(grid);

        for (i=0; i<9; i++)
            board[row][i]= grid[i];
    }
    for(row=2; row<9; row++)
    {
        randomRow(grid);

        for (i=0; i<9; i++)
            board[row][i]= grid[i];

    }
    printf("\n");
    printGrid(board);
    return 0;
}

