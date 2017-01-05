# Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
OBJS = problem.o solution.o gasolver.o population.o genetic_test.o
# Executable name
EXENAME = a.out

# Macros
CC = g++
CCOPTS = -std=c++11 -c -g -O0 -Wall -Wno-deprecated
LINK = g++
LINKOPTS = -o

#g++ -std=c++11 tostring.cpp

all : $(EXENAME)



# The compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS)


# Object files
genetic_test.o : genetic_test.cpp
	$(CC) $(CCOPTS) genetic_test.cpp

problem.o : common/Problem.cpp common/Problem.h
	$(CC) $(CCOPTS) common/Problem.cpp
solution.o : common/Solution.cpp common/Solution.h
	$(CC) $(CCOPTS) common/Solution.cpp

gasolver.o : ga/GASolver.cpp ga/GASolver.h
	$(CC) $(CCOPTS) ga/GASolver.cpp
population.o : ga/Population.cpp ga/Population.h
	$(CC) $(CCOPTS) ga/Population.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null