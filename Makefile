# Makefile for project 'tdmecpp'

CPP = g++
LD = g++
CPP_FLAGS = -Wall -g
LD_FLAGS = 

BIN_DIR = bin
LIB_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = includes

LIB = $(LIB_DIR)/libtdme.so
LIBTDME_INCLUDE = -I$(INC_DIR)

# set platform specific flags
OS := $(shell sh -c 'uname -s 2>/dev/null')
ifeq ($(OS), Linux)
	LIBNAME = -soname
else ifeq ($(OS), NetBSD)
	LIBNAME = -soname
else ifeq ($(OS), Darwin)
	LIBNAME = -install_name
endif

# Lists of necessary source files and object files for building libtdme
MATH_SRC_FILES := $(wildcard $(SRC_DIR)/libtdme/math/*.cpp)

LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/math/,$(notdir $(MATH_SRC_FILES:.cpp=.o)))


###############################################################################
# TARGETS

all: libtdme

install:
	test -z "/usr/lib" || mkdir -p "/usr/lib"
	cp $(LIB) /usr/lib
	test -z "/usr/include" || mkdir -p "/usr/include"
	cp -r $(INC_DIR)/libtdme /usr/include

uninstall:
	rm -f /usr/local/lib/libtdme.so
	rm -rf /usr/local/include/libtdme


###############################################################################
# build shared library from all libtdme object files
libtdme: $(LIBTDME_OBJ_FILES)
	test -d $(LIB_DIR) || mkdir -p $(LIB_DIR)
	$(LD) $(LD_FLAGS) -shared -Wl,$(LIBNAME),libtdme.so -o $(LIB) $(LIBTDME_OBJ_FILES) -lc $(LIBTDME_INCLUDE)

###############################################################################
# rules for building all libtdme object files

$(OBJ_DIR)/math/%.o: $(SRC_DIR)/libtdme/math/%.cpp
	test -d $(OBJ_DIR)/math || mkdir -p $(OBJ_DIR)/math
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

###############################################################################
doxygen: 
	doxygen ./docs/doxyfile


###############################################################################
# rule for cleaning up
clean:
	rm -frv $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR)


.PHONY: all libtdme clean install unistall
