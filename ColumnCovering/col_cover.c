#include <stdio.h>
#include <stdlib.h>

int CoveredAllRows(int **matrix, int colsSelected[], int X, int Y) {
    for (int i = 0; i < X; i++) {
        int rowCovered = 0;
        for (int j = 0; j < Y; j++) {
            if (colsSelected[j] && matrix[i][j]) {
                rowCovered = 1;
                break; 
            }
        }
        if (!rowCovered) return 0; 
    }
    return 1; 
}

void Cost(int **matrix, int colsSelected[], int col, int *minCount, int **bestCols, int *numSolutions, int X, int Y, int weights[], int minWeights[], int primeCols[]) {
    if (col == Y) {
        if (CoveredAllRows(matrix, colsSelected, X, Y)) {
            int currentCount = 0;
            int currentWeight = 0;
            for (int i = 0; i < Y; i++) {
                currentCount += colsSelected[i];
                currentWeight += colsSelected[i] * weights[i];
            }
            if (currentCount < *minCount || (currentCount == *minCount && currentWeight < minWeights[0])) {
                *minCount = currentCount;
                *numSolutions = 1;
                minWeights[0] = currentWeight;
                for (int i = 0; i < Y; i++) {
                    bestCols[0][i] = colsSelected[i];
                }
            } else if (currentCount == *minCount && currentWeight == minWeights[0]) {
                minWeights[*numSolutions] = currentWeight;
                for (int i = 0; i < Y; i++) {
                    bestCols[*numSolutions][i] = colsSelected[i];
                }
                (*numSolutions)++;
            }
        }
        return;
    }
    if (primeCols[col]) {
        colsSelected[col] = 1; 
        Cost(matrix, colsSelected, col + 1, minCount, bestCols, numSolutions, X, Y, weights, minWeights, primeCols);
        return;  
    }

    colsSelected[col] = 1;
    Cost(matrix, colsSelected, col + 1, minCount, bestCols, numSolutions, X, Y, weights, minWeights, primeCols);
    colsSelected[col] = 0;
    Cost(matrix, colsSelected, col + 1, minCount, bestCols, numSolutions, X, Y, weights, minWeights, primeCols);
}

int main() {

    int X, Y;  
    int i, j;
    int x, y;
    scanf("%d %d", &X, &Y);    
    int *weights = (int *)malloc(Y * sizeof(int));  
    
    for (i = 0; i < Y; i++) {
        scanf("%d", &weights[i]);
    }
    
    int **matrix = (int **)malloc(X * sizeof(int *));  
    for (i = 0; i < X; i++) {
        matrix[i] = (int *)malloc(Y * sizeof(int));
        for (j = 0; j < Y; j++) {
            matrix[i][j] = 0;  
        }
    }

    while(scanf("%d %d", &x, &y) == 2){    	
        if(x == 0 && y == 0){
        	break;
		}        
        matrix[x - 1][y - 1] = 1;
	}
    
    printf("%d %d (Input X, Y)\n", X, Y);
    for (i = 0; i < Y; i++) {
        printf("%d ", weights[i]);
    }
    printf("(Input weight)\n");
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int *primeCols = (int *)malloc(Y * sizeof(int));
    for (i = 0; i < Y; i++) {
        primeCols[i] = 0;
    }

    for (i = 0; i < X; i++) {
        int countOnes = 0;
        int colIndex = -1;
        for (j = 0; j < Y; j++) {
            if (matrix[i][j] == 1) {
                countOnes++;
                colIndex = j;
            }
        }
        if (countOnes == 1) {
            primeCols[colIndex] = 1;
        }
    }

    int *colsSelected = (int *)malloc(Y * sizeof(int));
    for (i = 0; i < Y; i++) {
        colsSelected[i] = 0;
    }

    
    int minCount = Y + 1;
    int minWeights[Y];
    int numSolutions = 0;
    int **bestCols = (int **)malloc(Y * sizeof(int *));  
    for (i = 0; i < Y; i++) {
        minWeights[i] = 0;
        bestCols[i] = (int *)malloc(Y * sizeof(int));
        for (j = 0; j < Y; j++) {
            bestCols[i][j] = 0;
        }
    }

    Cost(matrix, colsSelected, 0, &minCount, bestCols, &numSolutions, X, Y, weights, minWeights, primeCols);

    printf("Number of minimum cover set found : %d\n", numSolutions);
    
    
    for (int s = 0; s < numSolutions; s++) {
        printf("The minimum column cover C : "); 
        int sum_weight = 0;             
        for (int i = 0; i < Y; i++) {
            if (bestCols[s][i]) {
                printf("%d ", i+1);
                sum_weight += weights[i];
            }
        }   
        printf("\ncost(C) = (|C|, weight(C)) : (%d, %d)\n", minCount, sum_weight);     
    }
    
    for (i = 0; i < Y; i++) {
        free(bestCols[i]);
    }
    free(bestCols);
    free(weights);
    free(colsSelected);
    free(primeCols);
    for (i = 0; i < X; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
