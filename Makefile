CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

OS_NAME:=$(shell uname -s | tr A-Z a-z)
ifeq ($(OS_NAME),darwin)
STDINCDIR := -I/opt/local/include
STDLIBDIR := -L/opt/local/lib
EXTRAFLAG := -Qunused-arguments
else
STDINCDIR := 
STDLIBDIR := 
EXTRAFLAG :=
endif

CPPFLAGS := $(shell root-config --cflags) $(STDINCDIR) $(EXTRAFLAG)
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lgsl -lgslcblas -lm

CPPFLAGS += -g

TARGET = simplot

SRC = simplot.cpp

OBJ = $(SRC:.cpp=.o)

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $<

clean :
	rm -f *.o $(TARGET) *~
