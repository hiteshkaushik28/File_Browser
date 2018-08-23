CC = g++
CFLAGS = -Wall -std=c++0x
DEPS = listing.h module2.h
OBJ = listing.o module2.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_browser: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
		-rm *.o $(objects) file_browser

