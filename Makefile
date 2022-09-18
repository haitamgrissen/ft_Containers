CC = clang++
FLAGS = --std=c++98 -Wall -Wextra -Werror

VECTORNAME = vector.out
MAPNAME = map.out 
STACKNAME = stack.out

VECTORSRC = TESTS/vector_tests.cpp
MAPSRC = TESTS/map_tests.cpp
STACKSRC = TESTS/stack_tests.cpp


all: 
	@echo "\n [Choose the Container to be tested A Mon Camarde!!] \n        (vector | map | stack)? \n"

vector: $(VECTORNAME)
$(VECTORNAME) : $(VECTORSRC)
	@$(CC) $(FLAGS)	$(VECTORSRC) -o $(VECTORNAME) && ./$(VECTORNAME)

map: $(MAPNAME)
$(MAPNAME) : $(MAPSRC)
	@$(CC) $(FLAGS)	$(MAPSRC)	-o  $(MAPNAME) && ./$(MAPNAME)

stack: $(STACKNAME)
$(STACKNAME) : $(STACKSRC)
	@$(CC) $(FLAGS)	$(STACKSRC) -o $(STACKNAME) && ./$(STACKNAME)

clean:
	rm -f $(VECTORNAME)  $(MAPNAME) $(STACKNAME)
fclean:
	rm -f $(VECTORNAME)  $(MAPNAME) $(STACKNAME)