# Name of the built binary
BINNAME = lass

# Source code directory
SRCDIR = src

# Include directory
IDIR = include

# Binary directory
BINDIR = build

# C++ Compiler and Flags
CXX = g++
CXX_FLAGS = -std=c++11 -Wall
CXX_INCLUDES = -I$(IDIR)

# Obj directory
ODIR = obj

# Additional pkg-config libraries
LIBS =

_DEPS = main.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: dirs
	@mkdir $(ODIR)
	@mkdir $(BINDIR)

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXX_INCLUDES) $(CXX_FLAGS)

all: $(OBJ)
	$(CXX) -o $@ $^  $(CXX_INCLUDES) $(CXX_FLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 