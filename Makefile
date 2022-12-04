TARGET  = word-counter

CC      = g++
SRCDIR  = src
OBJDIR  = output
CONF 	= -std=c++17 -lstdc++fs

test: word-counter
	$(OBJDIR)/word-counter $(arg1) $(arg2)

run: word-counter
	$(OBJDIR)/word-counter

word-counter: src/main.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $(OBJDIR)/word-counter $(SRCDIR)/main.cpp $(CONF)

