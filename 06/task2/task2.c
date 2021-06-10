//
// Created by weihs on 29/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int queenAllowed(int* occupiedColumns, int currentLine, int currentColumn) {
	for(int i = 0; i < currentLine; i++) {
		if(currentColumn == occupiedColumns[i]) return 0;
		if(currentColumn - occupiedColumns[i] == currentLine - i) return 0;
		if(currentColumn - occupiedColumns[i] == i - currentLine) return 0;
	}
	return 1;
}


void resetIfColumnIsDone(int* occupiedColumns, int* currentLine, int* currentColumn, int n) {
    while(*currentColumn == n) {
        (*currentLine)--;
        *currentColumn = occupiedColumns[*currentLine] + 1;
        occupiedColumns[*currentLine] = -1;
    }
}


int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("Usage: name <length>\n");
        exit(EXIT_FAILURE);
    }

    int n = (int) strtol((const char*) argv[1], NULL, 10);
	int* occupiedColumns = (int*) calloc((size_t) n, sizeof(int));
	for(int i = 0; i < n; i++) occupiedColumns[i] = -1;
    if(!occupiedColumns) goto cleanup;
    int currentLine = 0;
    int currentColumn = occupiedColumns[0] + 1;
    int solutions = 0;
	int res = 0;
	int flag = n % 2;

    double startTime = omp_get_wtime();
	while(1) {
		// every line contains a valid queen
		if(currentLine == n) {
			solutions++;
			currentLine--;
            currentColumn = occupiedColumns[currentLine] + 1;
			occupiedColumns[currentLine] = -1;
			resetIfColumnIsDone(occupiedColumns, &currentLine, &currentColumn, n);
			continue;
		}

		// if no queen is allowed in line currentLine then decrease line until there are allowed squares
		resetIfColumnIsDone(occupiedColumns, &currentLine, &currentColumn, n);

		if(currentColumn == n/2 && currentLine == 0 && !flag){
			res = 2 * solutions;
			break;
		}

		if(currentColumn == n/2 && currentLine == 0 && flag) {
			res = 2*solutions;
			solutions = 0;
		}

		if(currentColumn == n/2 + 1 && currentLine == 0 && flag){
			res += solutions;
			break;
		}

		// found a valid square to put a queen in line currentLine
	    if(currentColumn < n && queenAllowed(occupiedColumns, currentLine, currentColumn)) {
			// goto next line and mark square as occupied
			occupiedColumns[currentLine] = currentColumn;
			currentLine++;
			currentColumn = 0;
			continue;
		}

		// queen at (currentLine, currentColumn) is not allowed:
		if(currentColumn < n) {
			currentColumn++;
			continue;
		}

		break;  // redundant
    }
    double endTime = omp_get_wtime();

	printf("time = %.5f; result = %d\n", endTime - startTime, res);
	free(occupiedColumns);
    return EXIT_SUCCESS;

cleanup:
	free(occupiedColumns);
	return EXIT_FAILURE;
}
