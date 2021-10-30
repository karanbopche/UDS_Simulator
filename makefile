CC := g++
LIB := -pthread
SRCDIR := src
BUILDDIR  := build
TESTDIR := tests
BINDIR := bin
SPIKEDIR := spike
CFLAGS := -g -Wall -c
INCLUDE := -I includes

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SOURCES := $(call rwildcard, $(SRCDIR), *.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

TESTS := $(call rwildcard, $(TESTDIR), *.cpp)
TESTOBJECTS := $(TESTS:$(TESTDIR)/%.cpp=%.o)

SPIKES := $(wildcard $(SPIKEDIR)/*.cpp)
SPIKEOBJECTS := $(SPIKES:$(SPIKEDIR)/%.cpp=%.o)


all: $(OBJECTS)
	@echo "object files created."

# build spikes and run.
$(SPIKEOBJECTS):%.o: $(SPIKEDIR)/%.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $(BUILDDIR)/$@
	$(CC) $(BUILDDIR)/$@ $(OBJECTS) -o $(@:%.o=$(BINDIR)/%.exe) $(LIB)
	@echo "running spike "
	@$(@:%.o=$(BINDIR)/%.exe)

# build tests and run.
$(TESTOBJECTS):%.o: $(TESTDIR)/%.cpp $(OBJECTS) $(BUILDDIR)/TestCase.o
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $(BUILDDIR)/$@
	$(CC) $(BUILDDIR)/$@ $(BUILDDIR)/TestCase.o $(OBJECTS) -o $(@:%.o=$(BINDIR)/%.exe) $(LIB)
	@echo "running tests"
	@$(@:%.o=$(BINDIR)/%.exe)

$(BUILDDIR)/TestCase.o: $(TESTDIR)/TestCase.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

#create object files.
$(OBJECTS):$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	@echo "Cleaning..."
	rm -r -f $(BINDIR) 
	rm -r -f $(BUILDDIR)
	mkdir $(BUILDDIR)
	mkdir $(BINDIR)

.PHONY: clean

debug:
	@echo $(SPIKEOBJECTS)
