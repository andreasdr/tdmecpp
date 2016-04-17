# Makefile for project 'tdmecpp'

CPP = g++
LD = g++
CPP_FLAGS = -Wall -g -pthread
LD_FLAGS = -pthread
LIBS = -Lbin -lcurl -lcrypto

BIN_DIR = bin
LIB_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = includes

LIB = $(LIB_DIR)/libtdme.so
LIBTDME_INCLUDE = -I$(INC_DIR)
LIBTDME_LIBS = -lcurl -lcrypto

# set platform specific flags
OS := $(shell sh -c 'uname -s 2>/dev/null')
ifeq ($(OS), Linux)
	NETWORK_PLATFORM_SRC_DIR = $(SRC_DIR)/libtdme/platform/linux/network
	LIBNAME = -soname
else ifeq ($(OS), NetBSD)
	NETWORK_PLATFORM_SRC_DIR = $(SRC_DIR)/libtdme/platform/bsd/network
	LIBNAME = -soname
	LIBTDME_INCLUDE+= -I/usr/pkg/include
	LIBTDME_LIBS+= -L/usr/pkg/lib
	LIBS+= -L/usr/pkg/lib
else ifeq ($(OS), Darwin)
	NETWORK_PLATFORM_SRC_DIR = $(SRC_DIR)/libtdme/platform/bsd/network
	LIBNAME = -install_name
endif

# Lists of necessary source files and object files for building libtdme
GLOBAL_SRC_FILES := $(wildcard src/libtdme/globals/*.cpp)
JSON_SRC_FILES := $(wildcard src/libtdme/json/*.cpp)
MATH_SRC_FILES := $(wildcard $(SRC_DIR)/libtdme/math/*.cpp)
NETWORK_SRC_FILES := $(wildcard src/libtdme/network/*.cpp)
NETWORK_SRC_FILES += $(wildcard $(NETWORK_PLATFORM_SRC_DIR)/*.cpp)
NETWORK_SHARED_SRC_FILES := $(wildcard src/libtdme/network/shared/*.cpp)
HTTPCLIENT_SRC_FILES := $(wildcard src/libtdme/network/httpclient/*.cpp)
TCPSERVER_SRC_FILES :=  $(wildcard src/libtdme/network/tcpserver/*.cpp)
THREADING_SRC_FILES := $(wildcard src/libtdme/threading/*.cpp)
UDPSERVER_SRC_FILES :=  $(wildcard src/libtdme/network/udpserver/*.cpp)
PERSISTANCE_SRC_FILES := $(wildcard src/libtdme/persistance/*.cpp)
XML_SRC_FILES := $(wildcard src/libtdme/xml/*.cpp)

LIBTDME_OBJ_FILES := $(addprefix $(OBJ_DIR)/globals/,$(notdir $(GLOBAL_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/json/,$(notdir $(JSON_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/threading/,$(notdir $(THREADING_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/math/,$(notdir $(MATH_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/network/,$(notdir $(NETWORK_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/network/shared/,$(notdir $(NETWORK_SHARED_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/network/httpclient/,$(notdir $(HTTPCLIENT_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/network/tcpserver/,$(notdir $(TCPSERVER_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/network/udpserver/,$(notdir $(UDPSERVER_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/persistance/,$(notdir $(PERSISTANCE_SRC_FILES:.cpp=.o)))
LIBTDME_OBJ_FILES += $(addprefix $(OBJ_DIR)/xml/,$(notdir $(XML_SRC_FILES:.cpp=.o)))

# Lists of necessary source files and object files for building testings
TEST_SRC_FILES := $(wildcard src/tests/globals/*.cpp src/tests/json/*.cpp src/tests/threading/*.cpp src/tests/network/*.cpp src/tests/persistance/*.cpp src/tests/xml/*.cpp)
TEST_OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(TEST_SRC_FILES:.cpp=.o)))


###############################################################################
# macros containing a list of object files necessary for building OBJ_LIST_TARGET_NAME

OBJ_LIST_TEST_ENCODING = $(OBJ_DIR)/test_encoding.o
OBJ_LIST_TEST_MD5 = $(OBJ_DIR)/test_md5.o
OBJ_LIST_TEST_EXCEPTIONS = $(OBJ_DIR)/test_exceptions.o
OBJ_LIST_TEST_THREADING = $(OBJ_DIR)/test_threading.o \
                          $(OBJ_DIR)/TestThread.o \
                          $(OBJ_DIR)/ProducerThread.o \
                          $(OBJ_DIR)/ConsumerThread.o
OBJ_LIST_TEST_JSON = $(OBJ_DIR)/test_json.o
OBJ_LIST_TEST_ECHOTCPSERVER = $(OBJ_DIR)/test_echotcpserver.o \
					$(OBJ_DIR)/EchoTCPServer.o \
					$(OBJ_DIR)/EchoTCPServerClient.o
OBJ_LIST_TEST_ECHOUDPSERVER = $(OBJ_DIR)/test_echoudpserver.o \
					$(OBJ_DIR)/EchoUDPServer.o \
					$(OBJ_DIR)/EchoUDPServerClient.o
OBJ_LIST_TEST_HTTPCLIENT = $(OBJ_DIR)/test_httpclient.o
OBJ_LIST_TEST_COUCHDB = $(OBJ_DIR)/test_couchdb.o
OBJ_LIST_TEST_XML = $(OBJ_DIR)/xmltest.o


###############################################################################
# TARGETS

all: test_all

install:
	test -z "/usr/lib" || mkdir -p "/usr/lib"
	cp $(LIB) /usr/lib
	test -z "/usr/include" || mkdir -p "/usr/include"
	cp -r $(INC_DIR)/libtdme /usr/include

uninstall:
	rm -f /usr/local/lib/libtdme.so
	rm -rf /usr/local/include/libtdme

test_all: test_exceptions test_encoding test_md5 test_threading test_json test_echotcpserver test_echoudpserver test_httpclient test_couchdb test_xml

test_encoding: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_ENCODING) $(LD_FLAGS) $(LIBS)

test_md5: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_MD5) $(LD_FLAGS) $(LIBS)

test_exceptions: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_EXCEPTIONS) $(LD_FLAGS) $(LIBS)

test_threading: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_THREADING) $(LD_FLAGS) $(LIBS)

test_json: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_JSON) $(LD_FLAGS) $(LIBS)

test_echotcpserver: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_ECHOTCPSERVER) $(LD_FLAGS) $(LIBS)

test_echoudpserver: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_ECHOUDPSERVER) $(LD_FLAGS) $(LIBS)

test_httpclient: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_HTTPCLIENT) $(LD_FLAGS) $(LIBS)

test_couchdb: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_COUCHDB) $(LD_FLAGS) $(LIBS)

test_xml: libtdme test_objs
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(LD) -o $(BIN_DIR)/$@ $(OBJ_LIST_TEST_XML) $(LD_FLAGS) $(LIBS)

###############################################################################
# rules for building all object files for all testings

test_objs: $(TEST_OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/globals/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $(LIBTDME_INCLUDE) $< -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/json/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $(LIBTDME_INCLUDE) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/threading/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $(LIBTDME_INCLUDE) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/network/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $(LIBTDME_INCLUDE) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/persistance/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $(LIBTDME_INCLUDE) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/xml/%.cpp
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CPP) $(CPP_FLAGS) -c $(LIBTDME_INCLUDE) $< -o $@

###############################################################################
# build shared library from all libtdme object files
libtdme: $(LIBTDME_OBJ_FILES)
	test -d $(LIB_DIR) || mkdir -p $(LIB_DIR)
	$(LD) $(LD_FLAGS) -shared -Wl,$(LIBNAME),libtdme.so -o $(LIB) $(LIBTDME_OBJ_FILES) -lc $(LIBTDME_INCLUDE)

###############################################################################
# rules for building all libtdme object files

$(OBJ_DIR)/globals/%.o: $(SRC_DIR)/libtdme/globals/%.cpp
	test -d $(OBJ_DIR)/globals || mkdir -p $(OBJ_DIR)/globals
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/json/%.o: $(SRC_DIR)/libtdme/json/%.cpp
	test -d $(OBJ_DIR)/json || mkdir -p $(OBJ_DIR)/json
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/threading/%.o: $(SRC_DIR)/libtdme/threading/%.cpp
	test -d $(OBJ_DIR)/threading || mkdir -p $(OBJ_DIR)/threading
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/math/%.o: $(SRC_DIR)/libtdme/math/%.cpp
	test -d $(OBJ_DIR)/math || mkdir -p $(OBJ_DIR)/math
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/network/%.o: $(SRC_DIR)/libtdme/network/%.cpp
	test -d $(OBJ_DIR)/network || mkdir -p $(OBJ_DIR)/network
	test -d $(OBJ_DIR)/network/httpclient || mkdir -p $(OBJ_DIR)/network/httpclient
	test -d $(OBJ_DIR)/network/shared || mkdir -p $(OBJ_DIR)/network/shared
	test -d $(OBJ_DIR)/network/tcpserver || mkdir -p $(OBJ_DIR)/network/tcpserver
	test -d $(OBJ_DIR)/network/udpserver || mkdir -p $(OBJ_DIR)/network/udpserver
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/network/%.o: $(NETWORK_PLATFORM_SRC_DIR)/%.cpp
	test -d $(OBJ_DIR)/network || mkdir -p $(OBJ_DIR)/network
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/persistance/%.o: $(SRC_DIR)/libtdme/persistance/%.cpp
	test -d $(OBJ_DIR)/persistance || mkdir -p $(OBJ_DIR)/persistance
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

$(OBJ_DIR)/xml/%.o: $(SRC_DIR)/libtdme/xml/%.cpp
	test -d $(OBJ_DIR)/xml || mkdir -p $(OBJ_DIR)/xml
	$(CPP) -fPIC $(CPP_FLAGS) $(LIBTDME_INCLUDE) -c $< -o $@

###############################################################################
doxygen: 
	doxygen ./docs/doxyfile


###############################################################################
# rule for cleaning up
clean:
	rm -frv $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR)


.PHONY: all test_all test_exceptions test_threading test_json test_network test_httpclient test_couchdb libtdme clean check_os install unistall
