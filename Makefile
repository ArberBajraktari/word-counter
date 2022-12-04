TARGET   = word-counter

CC       = g++
SRCDIR   = src
OBJDIR   = output

start: word-counter
	$(OBJDIR)/word-counter

word-counter: src/main.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $(OBJDIR)/word-counter $(SRCDIR)/main.cpp -std=c++17 -lstdc++fs
