/*
 * main.c
 *
 *  Corbin Olsen
 *  CS 1412-003
 *  Project 1
 *
 *  scans in the name of the PGM and the amount of frames to compute and then calls all the functions.
 */
#include "gameoflife.h"

int main(int argc, char **argv){

	char pgmname[100];

	int frames;

	//printf("The name of the pgm file: \r\n");
	//scans in the name of the PGM file.
	scanf("%s", pgmname);

	//printf("The amount of frames: \r\n");
	//scans in the amount of frames necessary.
	scanf("%d", &frames);

	//reads in the PGM file and populates the PGM structure with the information.
	PGM pgm = readPGM(pgmname);

	//takes the pgm data and transfers the data into characters and adds the border of 'O's.
	char **newarray = popOs(pgm);

	//calculates each frame and prints it to the cmd line.
	nextframe(pgm, newarray, frames);

	return 0;
}
