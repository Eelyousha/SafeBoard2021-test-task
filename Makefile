OBJDIR := obj
SRCDIR := src
INCDIR := inc

objects := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

app.exe: $(objects)
	g++ -std=c++2a -O$(OBJDIR) -Wall -Werror -pedantic -o $@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	g++ -std=c++2a -I$(INCDIR) -Wall -Werror -pedantic -c $< -o $@
