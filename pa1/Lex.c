#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include<string.h>
#define MAX_WORD_LENGTH 256  // defined constant length of word
int main(int argc, char** argv)
{
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

	int count=0;
	char *line=(char*)malloc(MAX_WORD_LENGTH*sizeof(char));

	// Counting number of line in a input file

	while(fgets(line, MAX_WORD_LENGTH ,readFile)!=NULL)
	            count = count + 1;

	// Setting cursor at beginning.

    fseek(readFile, 0 , SEEK_SET);

    // Creating dynamic array for string and initializing size

    char **data=(char**)malloc((count)*sizeof(char*));
   int  i=0;
   for(i=0;i<count;i++)
   	   data[i]=(char*)malloc(MAX_WORD_LENGTH*sizeof(char));

   // Storing string from file to dynamic array.

    i=0;
    while(fgets(data[i], MAX_WORD_LENGTH ,readFile)!=NULL)
    {
    	data[i][strcspn(data[i],"\n")]=0;
    	i++;
    }

    // Initializing empty list by new list.

    List lexData=newList();
    for(i=0;i<count;i++)
    {
    	append(lexData,i);
    }

    // Arranging in lexicographic order.

    int tempindex, normalindex, setindex, normalSetindex;
    moveFront(lexData);
    for (moveNext(lexData);index(lexData)>=0;moveNext(lexData)) {
        tempindex = get(lexData);
        normalindex = index(lexData);
        normalSetindex=normalindex;
        normalindex=normalindex-1;
        movePrev(lexData);
        setindex=get(lexData);
        while (normalindex >= 0 && strcmp(data[setindex],data[tempindex])>0)
        {
             moveNext(lexData);
             set(lexData,setindex);
             movePrev(lexData);
             normalindex = normalindex - 1;
             movePrev(lexData);
             setindex=get(lexData);
        }
        if(index(lexData)>=0)
        {
          moveNext(lexData);
          set(lexData,tempindex);
        }
        else
        {
        	moveFront(lexData);
        	set(lexData,tempindex);
        }
        moveFront(lexData);
        for(int j=0; j<normalSetindex;j++) moveNext(lexData);
    }

    // Writing in output file.

    for(moveFront(lexData); index(lexData)>=0; moveNext(lexData)){
   	      fputs(data[get(lexData)],writeFile);
   	      fputs("\n", writeFile);
   	   }

    free(data);
    free(line);
    freeList(&lexData);
    fclose(readFile);
    fclose(writeFile);
    return 0;
}


