# Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
OBJS_GEN = Problem.o Solution.o CPLEXSolver.o GASolver.o Population.o main.o

OBJS_CPLEX_PSEUDO = Problem.o Solution.o CPLEXSolver.o benchmark_cplex_pseudo.o 
OBJS_CPLEX_RAND = Problem.o Solution.o CPLEXSolver.o benchmark_cplex_rand.o 

OBJS_GA_PSEUDO = Problem.o Solution.o GASolver.o Population.o  benchmark_ga_pseudo.o 
OBJS_GA_RAND = Problem.o Solution.o GASolver.o Population.o  benchmark_ga_rand.o 
# Executable name
EXENAME = main.out

# Macros
CC = g++
CCOPTS = -std=c++11 -c -g -O0 -Wall -Wno-deprecated -Wunused-variable -Wno-sign-compare
LINK = g++
LINKOPTS = -o


## OSX FLAG
#CPX_INCDIR  = /opt/CPLEX_Studio1263/cplex/include
#CPX_LIBDIR  = /opt/CPLEX_Studio1263/cplex/lib/x86-64_osx/static_pic
#CPX_LDFLAGS = -lcplex -lm -pthread
## Linux/LAB flag
CPX_INCDIR  = /opt/CPLEX_Studio/cplex/include
CPX_LIBDIR  = /opt/CPLEX_Studio/cplex/lib/x86-64_linux/static_pic
CPX_LDFLAGS = -lcplex -lm -pthread

#g++ -std=c++11 tostring.cpp

#### MAKE

all : $(EXENAME) cplex_pseudo cplex_rand ga_rand ga_pseudo ga_test

cplex_pseudo : $(OBJS_CPLEX_PSEUDO)
	$(CC) $(LINKOPTS) cplex_pseudo.out  $(OBJS_CPLEX_PSEUDO) -L$(CPX_LIBDIR) $(CPX_LDFLAGS)

cplex_rand : $(OBJS_CPLEX_RAND)
	$(CC) $(LINKOPTS) cplex_rand.out  $(OBJS_CPLEX_RAND) -L$(CPX_LIBDIR) $(CPX_LDFLAGS)

ga_pseudo : $(OBJS_GA_PSEUDO)
	$(CC) $(LINKOPTS) ga_pseudo.out  $(OBJS_GA_PSEUDO)

ga_rand : $(OBJS_GA_RAND)
	$(CC) $(LINKOPTS) ga_rand.out  $(OBJS_GA_RAND)

ga_test : Problem.o Solution.o CPLEXSolver.o GASolver.o Population.o genetic_test.o
	$(CC) $(LINKOPTS) ga_test.out  $(OBJS_GA_RAND)

# make normale
$(EXENAME) : $(OBJS_GEN)
	$(CC) $(LINKOPTS) $(EXENAME) $(OBJS_GEN) -L$(CPX_LIBDIR) $(CPX_LDFLAGS)


##### Objects

# Executables

benchmark_cplex_rand.o : benchmark_cplex_rand.cpp
	$(CC) $(CCOPTS) benchmark_cplex_rand.cpp -I$(CPX_INCDIR)
	
benchmark_cplex_pseudo.o : benchmark_cplex_pseudo.cpp
	$(CC) $(CCOPTS) benchmark_cplex_pseudo.cpp -I$(CPX_INCDIR)


benchmark_ga_rand.o : benchmark_ga_rand.cpp
	$(CC) $(CCOPTS) benchmark_ga_rand.cpp
	
benchmark_ga_pseudo.o : benchmark_ga_pseudo.cpp
	$(CC) $(CCOPTS) benchmark_ga_pseudo.cpp


main.o : main.cpp
	$(CC) $(CCOPTS) main.cpp -I$(CPX_INCDIR)


# Classes

genetic_test.o : genetic_test.cpp
	$(CC) $(CCOPTS) genetic_test.cpp

Problem.o : common/Problem.cpp common/Problem.h
	$(CC) $(CCOPTS) common/Problem.cpp
Solution.o : common/Solution.cpp common/Solution.h
	$(CC) $(CCOPTS) common/Solution.cpp

GASolver.o : ga/GASolver.cpp ga/GASolver.h
	$(CC) $(CCOPTS) ga/GASolver.cpp
Population.o : ga/Population.cpp ga/Population.h
	$(CC) $(CCOPTS) ga/Population.cpp

CPLEXSolver.o : cplex/CPLEXSolver.cpp cplex/CPLEXSolver.h
	$(CC) $(CCOPTS) cplex/CPLEXSolver.cpp -I$(CPX_INCDIR) 





clean :
	rm -f *.o *.out 2>/dev/null

.PHONY: clean