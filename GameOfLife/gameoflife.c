/*
 * gameoflife.c
 *
 *  Corbin Olsen
 *  CS 1412-003
 *  Project 1
 *
 * holds all the functions that the main uses to read the PGM file, populate an array with the info from the PGM, and then compute the next frames.
 *
 */

#include "gameoflife.h"

PGM readPGM(char *name){
	int i, j;
	FILE *file;
	//reads in the PGM file and populates the PGM structure with the information.
	PGM p = (PGM)malloc(sizeof(PGM_data));
	//opens the PGM file.
	file = fopen(name, "r");

	//scans in the type of PGM file, in this case it should be P2.
	fscanf(file, "%s", p->keyword);

	//tests to make sure it's a P2 PGM file.
	if(strcmp(p->keyword, "P2")){
		printf("You have the wrong file. \r\n");
		exit(EXIT_FAILURE);

	//Moves on if it is a P2 PGM file.
	}else{

		//scans in all the information from the PGM file.
		fscanf(file, "%d", &p->col);

		fscanf(file, "%d", &p->row);

		fscanf(file, "%d", &p->whitevalue);

		//sets up the array for the PGM file.
		p->array = (int **)malloc(sizeof(int *) * p->row);

		for(i = 0; i < p->row; i++){
			p->array[i] = (int *)malloc(sizeof(int) * p->col);
		}

		//populates the array with data from the PGM file.
		for(i= 0; i < p->row; i++){
			for(j = 0; j < p->col; j++){
				fscanf(file, "%d", &p->array[i][j]);
			}
		}

		return p;
	}
}
//takes the pgm data and transfers the data into characters and adds the border of 'O's.
char **popOs(PGM p){
	int i, j;
	char **newarray;
	//sets up a new array.
	newarray = (char **)malloc(sizeof(char *) * (p->row + 2));

	for(i = 0; i < (p->row + 2); i++){
		newarray[i] = (char *)malloc(sizeof(char) * (p->col + 2));
	}

	//populates the whole new array with 'O's.
	for(i = 0; i < p->row + 2; i++){
		for(j = 0; j < p->col + 2; j++){
			newarray[i][j] = 'O';
		}
	}


	//populates the inside of the new array with the data from the PGM data array.
	for(i = 0; i < p->row; i++){
		for(j = 0; j < p->col; j++){
			if(p->array[i][j] == p->whitevalue){
				newarray[i+1][j+1] = 'X';
			}
			else{
				newarray[i+1][j+1] = 'O';
			}
		}
	}
	return newarray;
}

//calculates each frame and prints it to the cmd line.
void nextframe(PGM p, char **newarray, int frames){
	int i, j, Xs;
	int currentframe = 1;
	char **nextarray;

	//sets up an array to hold the data for the next frame.
	nextarray = (char **)malloc(sizeof(char *) * (p->row+2));

	for(i = 0; i < p->row+2; i++){
		nextarray[i] = (char *)malloc(sizeof(char) * (p->col+2));
	}

	//prints the seed.
	printf("Seed: %d %d\r\n", p->col, p->row);
	for(i = 0; i < p->row+2; i++){
		for(j = 0; j < p->col+2; j++){
			printf("%c ", newarray[i][j]);
		}
		printf("\r\n");
	}

	printf("\r\n");

	//calculates all the next frames and prints them out.
	while (currentframe <= frames){
		printf("Frame: %d\r\n", currentframe);

		//fills in the next array with 'O's.
		for(i = 0; i < p->row+2; i++){
			for(j = 0; j < p->col+2; j++){
				nextarray[i][j] = 'O';
			}
		}

		//checks all the elements around the tested element and adds to the counter when it's an 'X'.
		for(i = 1; i < p->row+1; i++){
			for(j = 1; j < p->col+1; j++){
				Xs = 0;
				if(newarray[i-1][j-1] == 'X'){
					Xs++;
				}
				if(newarray[i-1][j] == 'X'){
					Xs++;
				}
				if(newarray[i-1][j+1] == 'X'){
					Xs++;
				}
				if(newarray[i][j+1] == 'X'){
					Xs++;
				}
				if(newarray[i+1][j+1] == 'X'){
					Xs++;
				}
				if(newarray[i+1][j] == 'X'){
					Xs++;
				}
				if(newarray[i+1][j-1] == 'X'){
					Xs++;
				}
				if(newarray[i][j-1] == 'X'){
					Xs++;
				}

				//populates the next array with new data that was determined by the current value and the amount of Xs surrounding it.
				if(newarray[i][j] == 'X' && Xs < 2){
					nextarray[i][j] = 'O';
				}
				if(newarray[i][j] == 'X' && (Xs == 2 || Xs == 3)){
					nextarray[i][j] = 'X';
				}
				if(newarray[i][j] == 'X' && Xs > 3){
					nextarray[i][j] = 'O';
				}
				if(newarray[i][j] == 'O' && Xs == 3){
					nextarray[i][j] = 'X';
				}
			}
		}

		//populates the old array with the next array.
		for(i = 0; i < p->row+2; i++){
			for(j = 0; j < p->col+2; j++){
				newarray[i][j] = nextarray[i][j];
			}
		}

		//prints out the next frame.
		for(i = 0; i < p->row+2; i++){
			for(j = 0; j < p->col+2; j++){
				printf("%c ", newarray[i][j]);
			}
			printf("\r\n");
		}

		currentframe++;
		printf("\r\n");
	}

}

