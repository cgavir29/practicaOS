SRCDIR := src
BUILDDIR := build
INCLUDE  := include
BINDIR := bin
LDFLAGS  := -pthread
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -I include

all: dirs $(BINDIR)/evaluador

VPATH := src include build

$(BINDIR)/evaluador: evaluador.o errs.o cast.o init.o reg.o ctrl.o rep.o stop.o
	$(CXX) -o $@ $(LDFLAGS) $^

$(BUILDDIR)/evaluador.o: evaluador.cpp errs.h cast.h init.h reg.h ctrl.h rep.h stop.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/errs.o: errs.cpp errs.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/cast.o: cast.cpp cast.h errs.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/init.o: init.cpp init.h errs.h cast.h 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/reg.o: reg.cpp reg.h errs.h cast.h 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/ctrl.o: ctrl.cpp ctrl.h errs.h cast.h 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/rep.o: rep.cpp rep.h errs.h cast.h 
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