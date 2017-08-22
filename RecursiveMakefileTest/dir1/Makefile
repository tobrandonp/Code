include ../Makefile.defs


TARGET_DIR:=obj

EXEC_TARGET=main
SRCS:=$(wildcard *.cpp)

EXT_SRCS:=../dir2/B.cpp
EXT_OBJS:=$(addprefix $(TARGET_DIR)/, $(notdir $(EXT_SRCS:.cpp=.o)))


OBJS:=$(addprefix $(TARGET_DIR)/, $(SRCS:.cpp=.o))



INCLUDES:=-I. \
          -I../dir2

all: $(EXEC_TARGET)


include ../Makefile.rules
