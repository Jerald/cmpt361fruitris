############################################################
# 
# Oscar's fancy awesome easy makefile!
#
# For help, consult Oscar only after you've
# thoroughly bashed your head against make.
#
############################################################

# Not sure if this actually works, but it's supposed
# to enable jobs on all invocations of this makefile
MAKEFLAGS := -j4

# Compiler
CC = clang++

# Compiler flags
flags = -std=c++17 -Wall -Wextra -Werror -Og -g
# Compiler flags for library linking
libs = -lGL -lGLU -lglut -lpthread

# Directory of source files
srcDir = ./src
# Extension of source files to compile
srcExt = .cpp

# Directory for object building
buildDir = ./build
# Extension of intermediate build files
buildExt = .o

# Final executable
target = FruitTetris

### Don't change manually
sources := $(shell find . -path '$(srcDir)/*$(srcExt)')
headers := $(shell find . -path '$(srcDir)/*.h')
objs = $(subst $(srcDir), $(buildDir), $(patsubst %$(srcExt), %$(buildExt), $(sources)))
### Don't change manually

$(target): $(objs)
	$(CC) $(flags) $(libs) $^ -o $@

$(buildDir)/%$(buildExt): $(srcDir)/%$(srcExt) $(headers)
	@mkdir -p $(buildDir)/$(*D)
	$(CC) $(flags) -c $< -o $@

.PHONY: clean makeTest start

start: $(target)
	@./$(target)

# Tests the make file by printing internal variables
makeTest:
	@echo Sources:		$(sources)
	@echo Objs:			$(objs)

# Cleans the build directory of object files as well as removes the executable
clean:
	rm -rf $(buildDir)/* $(target)