CXX=g++ -std=c++17
CXXFLAGS=-I/usr/local/include/vmxpi -L/usr/local/lib/vmxpi -lvmxpi_hal_cpp -lrt -lpthread -I./vmxpi_cpp/include -I./OmnidirectionalRobot/include -I./general/include

SRC_DIR_hardware = vmxpi_cpp/src
SOURCES=$(wildcard $(SRC_DIR_hardware)/*.cpp)
SRC_DIR_model = OmnidirectionalRobot/src
SOURCES+=$(wildcard $(SRC_DIR_model)/*.cpp)
SRC_DIR_general = general/src
SOURCES+=$(wildcard $(SRC_DIR_general)/*.cpp)

MAIN=$(wildcard *.cpp)

DEPS=$(SOURCES:.cpp=.d) 
BINS=$(SOURCES:.cpp=)

# If using GCC version higher than 6, additionally link to libatomic.so
GCCVERSION:=$(shell gcc -dumpversion | cut -f1 -d.)
GCCVERSIONGE7:=$(shell expr $(GCCVERSION) \>= 7)
ifeq "$(GCCVERSIONGE7)" "1"
CXXFLAGS += -latomic
endif

main:
	$(CXX) $(MAIN) $(SOURCES) -o $(MAIN:.cpp=) $(CXXFLAGS)


CLEAN = $(SOURCES)
CLEAN += $(MAIN)
clean: $(patsubst %.cpp, %.clean, $(CLEAN))

%.clean:
	rm -f $(@:.clean=)

run:
	sudo ./$(MAIN:.cpp=)


-include $(DEPS)
