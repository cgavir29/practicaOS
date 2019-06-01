SRCDIR := src
BUILDDIR := build
INCLUDE  := include
BINDIR := bin
LDFLAGS  := -pthread
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -I include

all: dirs $(BINDIR)/evaluador

VPATH := src include build

$(BINDIR)/evaluador: evaluador.o cast.o init.o reg.o ctrl.o rep.o stop.o
	$(CXX) -o $@ $(LDFLAGS) $^

$(BUILDDIR)/evaluador.o: evaluador.cpp cast.h init.h reg.h ctrl.h rep.h stop.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/cast.o: cast.cpp cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/init.o: init.cpp init.h cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/reg.o: reg.cpp reg.h cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/ctrl.o: ctrl.cpp ctrl.h cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/rep.o: rep.cpp rep.h cast.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/stop.o: stop.cpp stop.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<


clean:
	rm -f $(SRCDIR)/*.cpp~ makefile~
	rm -f -R $(BUILDDIR)
	rm -f -R $(BINDIR)

dirs:
	@test -d build || mkdir build
	@test -d bin || mkdir bin