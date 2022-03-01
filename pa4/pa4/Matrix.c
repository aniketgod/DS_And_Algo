#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
	Matrix mat=(Matrix)malloc(sizeof(MatrixObj));
	mat->n=n;
	mat->row=(List*)malloc((n+1)*sizeof(ListObj));
	for(int i=1;i<=n;i++)
	{
	mat->row[i]=newList();
	}
	return mat;
}

// Return the size of square Matrix M.
int size(Matrix M)
{
	if(M!=NULL)
	{
		return M->n;
	}
	return 0;
}
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
	int sum=0;
	for(int i=1;i<=M->n;i++)
		{
			sum=sum+length(M->row[i]);
		}
return sum;
}
void changeEntry(Matrix M, int i, int j, double x )
{
if(i>M->n||j>M->n || i<1 || j<1)
{
	return;
}
moveFront(M->row[i]);
Entry E=(Entry)malloc(sizeof(EntryObj));
E->column=j;
E->value=x;
int flag=0;
if(length(M->row[i])==0)
{
	flag=-1;
	 if(x==0)
	 {
		 return;
	 }
	append(M->row[i],E);
}
else
{
	   for(moveBack(M->row[i]); index(M->row[i])>=0; movePrev(M->row[i])){
	      Entry data=  (Entry)get(M->row[i]);
	      if(j==data->column)
	      {
	    	  flag=-1;
	    	  if(x==0)
	    	  {
	    		  delete(M->row[i]);
	    		  return;
	    	  }
	    	  set(M->row[i],E);
	    	  break;
	      }
	      else if(j>data->column)
	      {
	    	 if(x==0)
	    	 {
	    		 return;
	    	 }
	    	 flag=-1;
             insertAfter(M->row[i],E);
             break;
	      }
	   }
}
if(flag==0)
{
	 if(x==0)
	 {
		 return;
	 }
	prepend(M->row[i],E);
}

}
Matrix copy(Matrix A)
{
	Matrix M=newMatrix(A->n);
	int n=A->n;
	for(int i=1;i<=n;i++)
	{
		for(moveFront(A->row[i]);index(A->row[i])>=0;moveNext(A->row[i]))
		{
	           Entry data=(Entry)get(A->row[i]);
	           changeEntry(M,i,data->column,data->value);
		}
	}
	return M;
}
int equals(Matrix A, Matrix B)
{
if(A==NULL || B==NULL )
{
	return 0;
}
if(A->n!=B->n)
{
	return 0;
}
for(int i=1;i<=A->n;i++)
{
  if(length(A->row[i])!=length(B->row[i]))
  {
	  return 0;
  }
  moveFront(A->row[i]);
  for(moveFront(B->row[i]);index(B->row[i])>=0;moveNext(B->row[i]))
  {
	  Entry dataA=(Entry)get(A->row[i]);
	  Entry dataB=(Entry)get(B->row[i]);
	  if(dataA->column!=dataB->column || dataA->value!=dataB->value)
	  {
		  return 0;
	  }
	  moveNext(A->row[i]);
  }
}
return 1;
}
void printMatrix(FILE* out, Matrix M)
{

	for(int i=1;i<=M->n;i++)
	{
		if(length(M->row[i])==0)
		{
			continue;
		}
		fprintf(out,"%d:",i);
		 for(moveFront(M->row[i]); index(M->row[i])>=0; moveNext(M->row[i])){
			      Entry data=  (Entry)get(M->row[i]);
	               fprintf(out,"(%d, %.1f) ",data->column,data->value);
			   }
		fprintf(out,"\n");
	}
}
void helperSum(Matrix M, int i, List A, List B)
{
	Entry E=(Entry)malloc(sizeof(EntryObj));
	int flag=0;
	for(moveFront(A);index(A)>=0;moveNext(A))
	{
		flag=0;
		Entry aData=(Entry)get(A);
		for(moveFront(B);index(B)>=0;moveNext(B))
		{
              Entry bData=(Entry)get(B);
              if(aData->column==bData->column)
              {
            	flag=-1;
                if(aData->value+bData->value!=0)
                {
                E->column=aData->column;
                changeEntry(M,i,aData->column,aData->value+bData->value);
                break;
                }
              }
              else if(bData->column>aData->column)
              {
            	  break;
              }
		}
		if(flag==0)
		{
			changeEntry(M,i,aData->column,aData->value);
		}
	}

	for(moveFront(B);index(B)>=0;moveNext(B))
		{
			flag=0;
			Entry bData=(Entry)get(B);
			for(moveFront(A);index(A)>=0;moveNext(A))
			{
	              Entry aData=(Entry)get(A);
	              if(bData->column==aData->column)
	              {
	            	flag=-1;
	            	break;
	              }
	              else if(aData->column>bData->column)
	              {
	            	  break;
	              }
			}
			if(flag==0)
			{
				changeEntry(M,i,bData->column,bData->value);
			}
		}

}
Matrix sum(Matrix A, Matrix B)
{
	if(size(A)!=size(B) || size(A)==0)
	{
       return NULL;
	}
	Matrix M=newMatrix(A->n);
    int n=A->n;
	for(int i=1;i<=n;i++)
	{
		helperSum(M,i,A->row[i],B->row[i]);
	}
return M;
}
void helperDiff(Matrix M, int i, List A, List B)
{
	Entry E=(Entry)malloc(sizeof(EntryObj));
	int flag=0;
	for(moveFront(A);index(A)>=0;moveNext(A))
	{
		flag=0;
		Entry aData=(Entry)get(A);
		for(moveFront(B);index(B)>=0;moveNext(B))
		{
              Entry bData=(Entry)get(B);
              if(aData->column==bData->column)
              {
                  flag=-1;
                if(aData->value-bData->value!=0)
                {
                E->column=aData->column;
                changeEntry(M,i,aData->column,aData->value-bData->value);
                break;
                }

              }
              else if(bData->column>aData->column)
              {
            	  break;
              }
		}
		if(flag==0)
		{
			changeEntry(M,i,aData->column,aData->value);
		}
	}

	for(moveFront(B);index(B)>=0;moveNext(B))
		{
			flag=0;
			Entry bData=(Entry)get(B);
			for(moveFront(A);index(A)>=0;moveNext(A))
			{
	              Entry aData=(Entry)get(A);
	              if(bData->column==aData->column)
	              {
	            	flag=-1;
	            	break;
	              }
	              else if(aData->column>bData->column)
	              {
	            	  break;
	              }
			}
			if(flag==0)
			{
				changeEntry(M,i,bData->column,(-1)*bData->value);
			}
		}

}
Matrix diff(Matrix A, Matrix B)
{
	if(size(A)!=size(B) || size(A)==0)
	{
       return NULL;
	}
	Matrix M=newMatrix(A->n);
    int n=A->n;
	for(int i=1;i<=n;i++)
	{
		helperDiff(M,i,A->row[i],B->row[i]);
	}
return M;
}
Matrix scalarMult(double x, Matrix A)
{
Matrix M=newMatrix(A->n);
int n=A->n;
for(int i=1;i<=n;i++)
{
	for(moveFront(A->row[i]);index(A->row[i])>=0;moveNext(A->row[i]))
	{
           Entry data=(Entry)get(A->row[i]);
           changeEntry(M,i,data->column,(x*data->value));
	}
}
return M;
}

Matrix transpose(Matrix A)
{
	Matrix M=newMatrix(A->n);
	int n=A->n;
	for(int i=1;i<=n;i++)
	{
		for(moveFront(A->row[i]);index(A->row[i])>=0;moveNext(A->row[i]))
		{
	           Entry data=(Entry)get(A->row[i]);
	           changeEntry(M,data->column,i,data->value);
		}
	}
	return M;
}
double vectorDot(List P, List Q)
{
	double x=0;
	for(moveFront(P);index(P)>=0;moveNext(P))
		{

			Entry aData=(Entry)get(P);
			for(moveFront(Q);index(Q)>=0;moveNext(Q))
			{
	              Entry bData=(Entry)get(Q);
	              if(aData->column==bData->column)
	              {
                          x=x+(aData->value*bData->value);
	              }
			}
		}
return x;
}
Matrix product(Matrix A, Matrix B)
{
	if(A==NULL || B==NULL)
	{
		return NULL;
	}
if(A->n!=B->n)
{
return NULL;
}
Matrix C=transpose(B);
Matrix M=newMatrix(A->n);

for(int i=1;i<=A->n;i++)
{
	for(int j=1;j<=A->n;j++)
	{
		double x=vectorDot(A->row[i],C->row[j]);
		if(x!=0)
		{
			changeEntry(M,i,j,x);
		}
	}
}
return M;
}

void freeMatrix(Matrix *pM)
{
	if((*pM)!=NULL)
	{
		for(int i=1;i<=(*pM)->n;i++)
		{
	       freeList(&((*pM)->row[i]));
		}
	}
     free((*pM)->row);
	(*pM)=NULL;
}
void makeZero(Matrix M)
{

	if(M!=NULL)
	{
		for(int i=1;i<=M->n;i++)
		{
	       freeList(&(M->row[i]));
	       M->row[i]=newList();
		}
	}

}


