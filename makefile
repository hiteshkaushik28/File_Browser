CC = g++ -w
CFLAGS = -Wall -std=c++0x
DEPS = listing.h keypress.h
OBJ = listing.o file.o keypress.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_browser: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
		-rm *.o $(objects) file_browser

