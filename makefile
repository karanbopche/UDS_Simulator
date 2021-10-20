CC := g++
LIB := -pthread
SRCDIR := src
BUILDDIR  := build
TARGET := bin
SPIKEDIR := spike
CFLAGS := -g -Wall -c
INCLUDE := -I includes

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SOURCES := $(call rwildcard, src, *.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

SPIKECPPFILES := $(wildcard $(SPIKEDIR)/*.cpp)
SPIKEOBJFILES := $(SPIKECPPFILES:$(SPIKEDIR)/%.cpp=%.o)

all: $(OBJECTS)
	@echo "creating object files"

# build spikes and run.
$(SPIKEOBJFILES):%.o: $(SPIKEDIR)/%.cpp $(OBJECTS)
	@if not exist $(SPIKEDIR)/$(BUILDDIR) mkdir $(SPIKEDIR)/$(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $(SPIKEDIR)/$(BUILDDIR)/$@
	$(CC) $(SPIKEDIR)/$(BUILDDIR)/$@ $(OBJECTS) -o $(@:%.o=$(TARGET)/%.exe) $(LIB)
	@echo "running spike "
	@$(@:%.o=$(TARGET)/%.exe)


#create object files.
$(OBJECTS):$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	@if not $(dir $@) mkdir $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean: $(BUILDDIR) $(TARGET)
	@echo "Cleaning..."
	rm -r $(TARGET) 
	rm -r $(BUILDDIR)
	mkdir $(BUILDDIR)
	mkdir $(TARGET)

# in case if folders are not present create them first.
$(BUILDDIR):
	mkdir $(BUILDDIR)

$(TARGET):
	mkdir $(TARGET)

# tests
test:
	$(MAKE) -C "tests/"

# spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
