SRCDIR := src
BUILDDIR := build
BINDIR := bin
LDFLAGS  := -pthread
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -I include

all: dirs $(BINDIR)/evaluador 

VPATH := src build

$(BINDIR)/evaluador: evaluador.o
	$(CXX) -o $@ $(LDFLAGS) $^

$(BUILDDIR)/evaluador.o: evaluador.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(SRCDIR)/*.cpp~ makefile~
	rm -f -R $(BUILDDIR)
	rm -f -R $(BINDIR)

dirs:
	@test -d build || mkdir build
	@test -d bin || mkdir bin