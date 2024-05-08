CXX=g++
CXXFLAGS=-I/usr/local/include/vmxpi -L/usr/local/lib/vmxpi -lvmxpi_hal_cpp -lrt -lpthread -I/home/pi/Desktop/Mobile_Robot_VMXpi_HAL/vmxpi_cpp/include -I./include
SRC_DIR_cpp=/home/pi/Desktop/Mobile_Robot_VMXpi_HAL/vmxpi_cpp/src
SOURCES=$(wildcard $(SRC_DIR_cpp)/*.cpp)
SRC_DIR = src
SOURCES+=$(wildcard $(SRC_DIR)/*.cpp)


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
