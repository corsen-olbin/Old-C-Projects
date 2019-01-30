/*
 * gameoflife.h
 *  Corbin Olsen
 *  CS 1412-003
 *  Project 1
 *
 * declares the structure for the PGM and all the functions.
 */

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include "stdheader.h"

struct _PGM {
	char keyword[4];
	int row;
	int col;
	int whitevalue;
	int **array;
};

typedef struct _PGM PGM_data;
typedef struct _PGM* PGM;

PGM readPGM(char *);
char **popOs(PGM);
void nextframe(PGM, char **, int);

#endif /* GAMEOFLIFE_H_ */
