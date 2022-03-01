#------------------------------------------------------------------------------
#  make                     makes FindPath
#  make GraphTest         makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c11 -Wall -c
LINK           = gcc -std=c11 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full


GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

checkClient : GraphTest
	$(MEMCHECK) GraphTest
