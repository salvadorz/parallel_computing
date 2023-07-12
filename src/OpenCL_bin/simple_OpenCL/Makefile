#include header files for external libraries
INCLUDE_DIRS = -I/opt/OpenCL/ICD-Loader/include
#Dir of external libraries
LIB_DIRS = -L/opt/OpenCL/ICD-Loader/lib
#Compiler
CXX=g++

CDEFS=
#Compiler Options
CFLAGS= -Wall -Wextra -g -O0 $(INCLUDE_DIRS) $(CDEFS)
#Linker Options
LDFLAGS = -Wl,$(LIB_DIRS) $(LIBS)
# Link with this libs
LIBS= -lOpenCL

HFILES= utility.h
CFILES= simple_OpenCL.cpp utility.cpp

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.cpp=.o}

TARGET = final_binary

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

depend:

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET) $(OBJS:.o=.d)
