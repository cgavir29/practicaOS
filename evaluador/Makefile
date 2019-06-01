SRCDIR := src
BUILDDIR := build
INCLUDE  := include
BINDIR := bin
LDFLAGS  := -pthread
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -I include

all: dirs $(BINDIR)/evaluador

VPATH := src include build

$(BINDIR)/evaluador: evaluador.o cast.o init.o
	$(CXX) -o $@ $(LDFLAGS) $^

$(BUILDDIR)/evaluador.o: evaluador.cpp cast.h init.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/cast.o: cast.cpp cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/init.o: init.cpp init.h cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<



clean:
	rm -f $(SRCDIR)/*.cpp~ makefile~
	rm -f -R $(BUILDDIR)
	rm -f -R $(BINDIR)

dirs:
	@test -d build || mkdir build
	@test -d bin || mkdir bin