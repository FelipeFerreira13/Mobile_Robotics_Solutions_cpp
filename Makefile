CXX=g++ -std=c++17
CXXFLAGS=-I/usr/local/include/vmxpi -std=c++17 -L/usr/local/lib/vmxpi -lvmxpi_hal_cpp -lrt -lpthread 

INC_DIR = -I./vmxpi_cpp/include -I./OmnidirectionalRobot/include -I./Object_Management_System/include -I./general/include #-lcobra
CXXFLAGS+=$(INC_DIR)

SRC_DIR_hardware = vmxpi_cpp/src
SOURCES=$(wildcard $(SRC_DIR_hardware)/*.cpp)
SRC_DIR_model = OmnidirectionalRobot/src
SOURCES+=$(wildcard $(SRC_DIR_model)/*.cpp)
SRC_DIR_oms = Object_Management_System/src
SOURCES+=$(wildcard $(SRC_DIR_oms)/*.cpp)
SRC_DIR_general = general/src
SOURCES+=$(wildcard $(SRC_DIR_general)/*.cpp)

MAIN=$(wildcard *.cpp)

DEPS=$(SOURCES:.cpp=.d) 
BINS=$(SOURCES:.cpp=)

OBJS=$(SOURCES:.cpp=.o)
OBJS+=$(MAIN:.cpp=.o)

# If using GCC version higher than 6, additionally link to libatomic.so
GCCVERSION:=$(shell gcc -dumpversion | cut -f1 -d.)
GCCVERSIONGE7:=$(shell expr $(GCCVERSION) \>= 7)
ifeq "$(GCCVERSIONGE7)" "1"
CXXFLAGS += -latomic
endif

main: $(OBJS)
	$(CXX) $(OBJS) -o $(MAIN:.cpp=) $(CXXFLAGS)

CLEAN = $(SOURCES)
CLEAN += $(MAIN)
clean: $(patsubst %.cpp, %.clean, $(CLEAN))

%.clean:
	rm -f $(@:.clean=)

clean_all:
	rm -f $(OBJS)

run:
	sudo ./$(MAIN:.cpp=)


-include $(DEPS)
