#include <stdbool.h>
#ifndef LIST_H_
#define LIST_H_
typedef struct NodeObj
{
	void* data;
	struct NodeObj *prev;
	struct NodeObj *next;
}Node;

typedef struct
{
int len;
int index;
Node *front;
Node *back;
Node *cursor;
}ListObj;

typedef ListObj *List;

Node* nodeConstructor(int, Node*, Node* );
void nodeDestructor(Node* );
List newList();
int length(List);
int index(List);
void* front(List);
void* back(List);
void* get(List);
void clear(List );
void* set(List , void* );
void moveFront(List );
void moveBack(List );
void movePrev(List );
void moveNext(List );
void prepend(List , void* );
void append(List , void* );
void insertBefore(List , void* );
void insertAfter(List , void* );
void deleteFront(List);
void deleteBack(List);
void delete(List);
List concatList(List , List );
void freeList(List* );

#endif /* LIST_H_ */
