CC = clang++
FLAGS = --std=c++98 -Wall -Wextra -Werror

VECTORNAME = vector.out
MAPNAME = map.out 
STACKNAME = stack.out

VECTORSRC = TESTS/vector_tests.cpp
MAPSRC = TESTS/map_tests.cpp
STACKSRC = TESTS/stack_tests.cpp

vector: $(VECTORNAME)
$(VECTORNAME) : $(VECTORSRC)
	@$(CC) $(FLAGS)	TESTS/vector_tests.cpp -o $(VECTORNAME)

map: $(MAPNAME)
$(MAPNAME) : $(MAPSRC)
	@$(CC) $(FLAGS)	TESTS/map_tests.cpp 	-o  $(MAPNAME)

stack: $(STACKNAME)
$(STACKNAME) : $(STACKSRC)
	@$(CC) $(FLAGS)	TESTS/stack_tests.cpp -o $(STACKNAME)

clean:
	rm -f $(VECTORNAME)  $(MAPNAME) $(STACKNAME)