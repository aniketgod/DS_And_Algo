#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "List.h"
#define UNDEF -1
#define NIL 0

typedef struct
{
int order;
int checkDG;
List* neighbour;
int* color;
int* parent;
int* discoverTime;
int* finishTime;
}GraphObj;
typedef GraphObj *Graph;

typedef struct {
    List stack;
} StackObj;
typedef StackObj *Stack;
Stack createStack()
{
     Stack stack = (Stack)malloc(
        sizeof(StackObj));
    stack->stack=newList();
    return stack;
}
int isEmpty(Stack s)
{
	if( s->stack->len <= 0)
	{
		return 0;
	}
    return s->stack->len;
}
void push(Stack s, int item)
{
    append(s->stack, item);
}
void pop(Stack s)
{
    deleteBack(s->stack);
}
int top(Stack s)
{
	return back(s->stack);
}
Graph newGraph(int n)
{
Graph graph=(Graph)malloc(sizeof(GraphObj));
graph->order=n;
graph->checkDG=0;
graph->neighbour=(List*)malloc((n+1)*sizeof(List));
graph->color=(int*)malloc((n+1)*sizeof(int));
graph->discoverTime=(int*)malloc((n+1)*sizeof(int));
graph->finishTime=(int*)malloc((n+1)*sizeof(int));
graph->parent=(int*)malloc((n+1)*sizeof(int));
for(int i=1;i<=n;i++)
{
graph->neighbour[i]=newList();
}
return graph;
}
int getOrder(Graph G)
{
return G->order;
}
int getSize(Graph G)
{
int size=0;
for(int i=1;i<=G->order;i++)
{
size=size+G->neighbour[i]->len;
}
if(G->checkDG==1)
{
return size;
}
int result=size/2;
return result;
}
int getParent(Graph G, int u)
{
	if(u<=0 || u>G->order)
	{
		return -1;
	}
return G->parent[u];
}
int getDiscover(Graph G, int u)
{
	if(u<=0 || u>G->order)
	{
		return -1;
	}
return G->discoverTime[u];
}
int getFinish(Graph G, int u)
{
	if(u<=0 || u>G->order)
	{
		return -1;
	}
return G->finishTime[u];
}
void addEdge(Graph G, int u, int v)
{
	if(u>G->order || v>G->order ||u<1 ||v<1)
	{
           return;
	}

	int flag=0;

	for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u]))
	{
		       if(get(G->neighbour[u])==v)
		       {
		    	   flag=-1;
		    	   break;
		       }
     }
		if(flag==0)
	{

			if(front(G->neighbour[u])==-1)
			{
				append(G->neighbour[u],v);
			}
			else
			{
				if(front(G->neighbour[u])>v)
				{
				prepend(G->neighbour[u],v);
				}
				else if(back(G->neighbour[u])<v)
				{

					append(G->neighbour[u],v);
				}
				else
				{
					for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u]))
					{

						if(get(G->neighbour[u])>v)
					{
					insertBefore(G->neighbour[u],v);
					break;
					}
					}
				}


			}
////
if(front(G->neighbour[v])==-1)
	{
		append(G->neighbour[v],u);
	}
	else
	{
		if(front(G->neighbour[v])>u)
		{
		prepend(G->neighbour[v],u);
		}
		else if(back(G->neighbour[v])<u)
		{
			append(G->neighbour[v],u);
		}
		else
		{

		for(moveFront(G->neighbour[v]); index(G->neighbour[v])>=0; moveNext(G->neighbour[v]))
		{
			if(get(G->neighbour[v])>u)
		{
		insertBefore(G->neighbour[v],u);
		break;
		}
		}
		}


	}


	}

}

void addArc(Graph G, int u, int v)
{
	if(u>G->order || v>G->order ||u<1 ||v<1)
	{
           return;
	}
	G->checkDG=1;
	int flag=0;
	for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u])){
		       if(get(G->neighbour[u])==v)
		       {
		    	   flag=-1;
		    	   break;
		       }
		   }

	if(flag==0)
{
		if(front(G->neighbour[u])==-1)
			{
				append(G->neighbour[u],v);
			}
			else
			{
				if(front(G->neighbour[u])>v)
				{
				prepend(G->neighbour[u],v);
				}
				else if(back(G->neighbour[u])<v)
				{

					append(G->neighbour[u],v);
				}
				else
				{
					for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u]))
					{

						if(get(G->neighbour[u])>v)
					{
					insertBefore(G->neighbour[u],v);
					break;
					}
					}
				}


			}

}
}

void printGraph(FILE* out, Graph G)
{
for(int i=1;i<=G->order;i++)
{
	fprintf(out,"%d: ",i);
	for(moveFront(G->neighbour[i]); index(G->neighbour[i])>=0; moveNext(G->neighbour[i])){
            fprintf(out,"%d ",get(G->neighbour[i]));

		   }
	fprintf(out,"\n");
}
}

//

void Visit(Graph G, int x, int* time)
{
	*time=*time+1;
	G->discoverTime[x]=*time;
	G-> color[x]=1;
	for(moveFront(G->neighbour[x]); index(G->neighbour[x])>=0; moveNext(G->neighbour[x])){
            if(G->color[get(G->neighbour[x])]==0)
            	{
            	G->parent[get(G->neighbour[x])]=x;
            	Visit(G, get(G->neighbour[x]), time);
            	}
		   }
	G->color[x]=2;
	*time=*time+1;
	G->finishTime[x]=*time;

}
void DFS(Graph G, List S)
{

	for(moveFront(S); index(S)>=0; moveNext(S)){
			        G->color[get(S)] = 0; // white
			        G->parent[get(S)] = 0;
				   }
	int* time;
	time=(int*)malloc(sizeof(int));
	*time=0;
	for(moveFront(S); index(S)>=0; moveNext(S)){

		if(get(S)>0)
		{
			 if(G->color[get(S)]==0) Visit(G,get(S), time) ;
		}


}

Stack L=createStack();
for(moveFront(S);index(S)>=0;moveNext(S))
{
append(L->stack,get(S));
}
Stack M=createStack();
while (isEmpty(L)>0)
    {
        // pop out the first element
        int tmp = top(L);
        pop(L);
       while (isEmpty(M)>0 && G->finishTime[top(M)] < G->finishTime[tmp] )
        {

           push(L,top(M));
           pop(M);

       }
        push(M,tmp);
    }

moveFront(M->stack);
for(moveFront(S);index(S)>=0;moveNext(S))
{
	set(S,get(M->stack));
	moveNext(M->stack);
}
freeList(&(M->stack));
}


// transpose of DG
Graph transpose(Graph G)
{
	Graph newG=newGraph(G->order);
	if(G->checkDG==0) return newG;
	newG->checkDG=1;

for(int i=1; i<=G->order; i++)
{
	for(moveFront(G->neighbour[i]); index(G->neighbour[i])>=0; moveNext(G->neighbour[i])){
    addArc(newG,get(G->neighbour[i]),i);
   }
}
return newG;
}
// copy the graph and return it
Graph copyGraph(Graph G)
{
Graph newG=newGraph(G->order);
newG->checkDG=G->checkDG;
if(newG->checkDG==0)
{
	for(int i=1; i<=G->order; i++)
	{
		for(moveFront(G->neighbour[i]); index(G->neighbour[i])>=0; moveNext(G->neighbour[i])){
	    addEdge(newG,i,get(G->neighbour[i]));
	   }
	}
}
else
{
	for(int i=1; i<=G->order; i++)
	{
		for(moveFront(G->neighbour[i]); index(G->neighbour[i])>=0; moveNext(G->neighbour[i])){
	    addArc(newG,i,get(G->neighbour[i]));
	   }
	}
}
for(int i=1;i<=G->order;i++)
{
	newG->discoverTime[i]=G->discoverTime[i];
	newG->finishTime[i]=G->finishTime[i];
}

return newG;
}
void freeGraph(Graph* pG)
{
	if((*pG)!=NULL)
	{
		for(int i=1;i<=(*pG)->order;i++)
		{
	       freeList(&((*pG)->neighbour[i]));
		}
		free((*pG)->neighbour);
		free((*pG)->color);
		free((*pG)->discoverTime);
		free((*pG)->finishTime);
		free((*pG)->parent);
		free((*pG));
	}

	(*pG)=NULL;
}
