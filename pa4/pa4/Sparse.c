#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
	 int n=0, nA=0, nB=0;
	 int row=0, column=0;
	 double data=0;
     Matrix A, B, C, D, E, F, G, H, I, J;
	// Checking number of argument provided is write or wrong.
    if(argc!=3)
    {
    	fprintf( stderr, "The %d number of argument provided. We need two number of arguments.", argc-1);
        exit(1);
    }

    // Opening file for reading and writing

	FILE* readFile=fopen(argv[1],"r");
	FILE* writeFile=fopen(argv[2],"w");

	// Checked file processing

    if(readFile==NULL)
    {
    	fprintf(stderr,"The error in processing file.");
    	exit(1);
    }


 if(fscanf(readFile,"%d %d %d",&n,&nA,&nB)!=EOF)
 {
   A=newMatrix(n);
   B=newMatrix(n);
 }
 for(int i=1;i<=nA;i++)
 {
	 if(fscanf(readFile,"%d %d %lf",&row,&column,&data)!=EOF)
	 {
		changeEntry(A,row,column,data);
	 }
 }
 for(int i=1;i<=nB;i++)
 {
	 if(fscanf(readFile,"%d %d %lf",&row,&column,&data)!=EOF)
	 {
		changeEntry(B,row,column,data);
	 }
 }
fprintf(writeFile,"A has %d non-zero entries:\n",NNZ(A));
printMatrix(writeFile,A);
fprintf(writeFile,"\n");
fprintf(writeFile,"B has %d non-zero entries:\n",NNZ(B));
printMatrix(writeFile,B);
fprintf(writeFile,"\n");
fprintf(writeFile,"(1.5)*A =\n");
C= scalarMult(1.5, A );
printMatrix(writeFile,C);
fprintf(writeFile,"\n");
fprintf(writeFile,"A+B =\n");
D = sum(A, B);
printMatrix(writeFile, D);
fprintf(writeFile,"\n");
fprintf(writeFile,"A+A =\n");
E = sum(A, A);
printMatrix(writeFile, E);
fprintf(writeFile,"\n");
fprintf(writeFile,"B-A =\n");
F = diff(B, A);
printMatrix(writeFile, F);
fprintf(writeFile,"\n");
fprintf(writeFile,"A-A =\n");
G = diff(A, A);
printMatrix(writeFile, G);
fprintf(writeFile,"\n");
fprintf(writeFile,"Transpose(A) =\n");
H = transpose(A);
printMatrix(writeFile, H);
fprintf(writeFile,"\n");
fprintf(writeFile,"A*B =\n");
I = product(A,B);
printMatrix(writeFile, I);
fprintf(writeFile,"\n");
fprintf(writeFile,"B*B =\n");
J = product(B,B);
printMatrix(writeFile, J);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);
   return 0;
}
