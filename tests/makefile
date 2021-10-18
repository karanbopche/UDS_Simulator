CPPFILES := $(wildcard *.cpp)
TESTBUILDDIR := TestBuild
TESTBINDIR := TestBin
CC := g++
CFLAGS := -c -g -Wall
INCLUDE := -I ../includes
OUTPUTFILES := $(CPPFILES:%.cpp=$(TESTBUILDDIR)/%.o)
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
OBJECTS := $(call rwildcard, ../build, *.o)

TESTFRAMEWORKFILES := testCase.cpp
TESTFRAMEWORKOBJ := $(TESTBUILDDIR)/$(TESTFRAMEWORKFILES:.cpp=.o)


Test: $(OUTPUTFILES) build
	@for %%i in ($(subst /,\,$(wildcard $(TESTBINDIR)/*.exe))) do %%i

$(OUTPUTFILES):$(TESTBUILDDIR)/%.o:%.cpp TestBuild/testCase.o
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
	$(CC) $(OBJECTS) $(TESTFRAMEWORKOBJ) $@ -o $(TESTBINDIR)/$(<:.cpp=.exe)

TestBuild/testCase.o:testCase.cpp testCase.h
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

#build project before running tests.
build: ../makefile
	$(MAKE) -C "../"

clean:$(TESTBUILDDIR) $(TESTBINDIR)
	rmdir $(TESTBUILDDIR) /Q /S
	rmdir $(TESTBINDIR) /Q /S
	mkdir $(TESTBUILDDIR)
	mkdir $(TESTBINDIR)

# rules for build folders.
$(TESTBINDIR):
	mkdir $(TESTBINDIR)

$(TESTBUILDDIR):
	mkdir $(TESTBUILDDIR)

.PHONY: clean

test_runall:
	@for %%i in ($(subst /,\,$(wildcard $(TESTBINDIR)/*.exe))) do %%i
