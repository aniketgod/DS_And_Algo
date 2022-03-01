//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int util(Graph G, int i, int * color)
{
int num=0;
color[i]=true;
for(moveFront(G->neighbour[i]);index(G->neighbour[i])>=0;moveNext(G->neighbour[i]))
{
if(color[get(G->neighbour[i])]==0)
{
	num=util(G, get(G->neighbour[i]), color);
}
}
num++;
return num;
}
int main(int argc, char* argv[]){
	int n=0, a=0, b=0;
	 List S=newList();

		 Graph G = NULL;
		 Graph T=NULL;
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

	    if(fscanf(readFile,"%d",&n)!=EOF)
	    G = newGraph(n);
	    for(int i=1;i<=n;i++)
	    {
	       append(S,i);
	    }
	    while(fscanf(readFile,"%d%d",&a,&b)!=EOF)
	   	 {
	   	 if(a==0 && b==0) break;
         addArc(G,a,b);
	   	 }
	    fprintf(writeFile,"Adjacency list representation of G:\n");
         printGraph(writeFile, G);
         DFS(G,S);
         printList(stdout,S);
         T=transpose(G);
         DFS(T,S);

int count=0;
      int* color=(int*)malloc((n+1)*sizeof(int));
for(int p=1;p<=G->order;p++)
{
	color[p]=0;
}
List L=newList();
for(moveFront(S);index(S)>=0;moveNext(S))
{
append(L,get(S));
}
while(S->len>0)
{
  int gh=back(S);
  deleteBack(S);
  if(color[gh]==0)
  {

	  util(T,gh,color);
	  count++;
	  printf("\n");
  }
}


fprintf(writeFile,"\nG contains %d strongly connected components:\n",count);
count=0;
for(moveFront(L);index(L)>=0;moveNext(L))
{
append(S,get(L));
}
for(int p=1;p<=G->order;p++)
{
	color[p]=0;
}
while(S->len>0)
{
  int gh=back(S);
  deleteBack(S);
  if(color[gh]==0)
  {
	  List temp=newList();
	  count++;
	  fprintf(writeFile,"Component %d: ",count);
	  int k=util(T,gh,color);
	  for(int i=0;i<k;i++)
	  {
		  prepend(temp,back(L));
		  deleteBack(L);
	  }
	  printList(writeFile,temp);
	  freeList(&temp);
	  fprintf(writeFile,"\n");
	  printf("\n");
  }
}

free(color);
freeGraph(&G);
freeList(&L);
freeList(&S);
        return(0);
}

