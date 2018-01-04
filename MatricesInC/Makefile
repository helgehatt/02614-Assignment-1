
SRCS 	= *.cpp
OBJS	= $(SRCS:.c=.o)
TARGET	= MatricesInC.$(CC)

CC		= g++
OPT		= -g -O3
CFLAGS	= $(OPT)

LIBS	= -L /usr/lib64/atlas -lsatlas

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -c stdafx.h -o stdafx.h.gch
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
