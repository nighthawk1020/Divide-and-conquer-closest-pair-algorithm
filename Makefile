COMPILER = g++
FLAGS = -g -Wall -std=c++0x
EXECUTABLE = submission
all: submission.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) submission.o

submission.o: submission.cpp
	$(COMPILER) $(FLAGS) -c submission.cpp

clean:
	rm -f *.o $(EXECUTABLE)
