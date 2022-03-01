
#ifndef MATRIX_H_
#define MATRIX_H_
#include "List.h"
typedef struct
{
int column;
double value;
}EntryObj;
typedef EntryObj* Entry;

typedef struct
{
	int n;
	List *row;
}MatrixObj;

typedef MatrixObj* Matrix;
Matrix newMatrix(int);
int size(Matrix);
int NNZ(Matrix);
void changeEntry(Matrix , int , int , double );
void printMatrix(FILE*,Matrix);
Matrix copy(Matrix);
int equals(Matrix , Matrix );
Matrix sum(Matrix , Matrix );
Matrix diff(Matrix , Matrix );
Matrix scalarMult(double , Matrix );
Matrix transpose(Matrix );
Matrix product(Matrix, Matrix);
void freeMatrix(Matrix*);
void makeZero(Matrix);

#endif /* MATRIX_H_ */
