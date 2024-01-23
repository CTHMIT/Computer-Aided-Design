# CAD #1 The Column Covering Problem

**Author:** NCHU 7111093024 EE715 C.T Hsu

## Execution Instructions

Execute the command on the terminal:

```PowerShell
gcc .\col_cover.c -o .\col_cover.exe
$files = @('bench1.txt', 'bench2.txt', 'bench3.txt', 'bench4.txt', 'bench5.txt', 'bench6.txt')
foreach ($file in $files) {
    Write-Host
    Write-Host "Reading $file..."
    Get-Content $file | .\col_cover.exe
}
##Data Structures and Variables:

	matrix: This is the input matrix of size X x Y. The value matrix[i][j] is 1 if row i is covered by column j, otherwise it's 0.
	weights: This is an array that contains the weights of each column.
	primeCols: This is an array that determines if a column is essential. A column is essential if it's the only column that can cover a specific row.
	colsSelected: It's an array that keeps track of which columns are currently selected.
	bestCols: It stores the columns of the best solutions found.

##Functions:

	CoveredAllRows(): Checks if all rows are covered by the currently selected columns.
	Cost(): A recursive function that tries every possible combination of columns to find the minimum set that covers all rows.

##Algorithm:

	The algorithm starts by reading the matrix's dimensions X and Y, and the weights of the columns.
	The matrix is initialized and filled based on the input, where pairs (x, y) indicate that row x is covered by column y.
	We then determine the essential columns. Essential columns are those that are the only columns covering a particular row. 
	We should always include these in our solution set as they are the only way to cover those specific rows.
	With all this setup done, the Cost() function is called to start the recursive search for the best solution.
	Finding the solutions, Printed out and memory freed.

##Note:

	The function Cost() uses backtracking that make a choice and recurse with that choice, and then undo that choice (backtrack) and make a different choice. 
	Selecting a column then find the optimal combination of columns.
	Memory is dynamically allocated for various arrays and matrices using malloc(), and free this memory at the end of the program to avoid memory leaks.

##Why:

	The backtracking approach, though potentially time-consuming, ensures all combinations are considered, providing a correct solution for the problem.
	Dynamic memory allocation allows for flexibility in the size of the matrix and other data structures.



