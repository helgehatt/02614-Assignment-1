TARGET	= libmatmult.so
LIBSRCS	= *.cpp
LIBOBJS	= $(LIBSRCS:.c=.o)

OPT	= -g
PIC	= -fPIC

CXX	= g++
CXXFLAGS= $(OPT) $(PIC) $(XOPTS)

SOFLAGS = -shared 
XLIBS	= -L /usr/lib64/atlas -lsatlas

$(TARGET): $(LIBOBJS)
	$(CXX) -o $@ $(SOFLAGS) $(LIBOBJS) $(XLIBS)

clean:
	@/bin/rm -f core core.* $(LIBOBJS) 
