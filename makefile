# change application name here (executable output name)
TARGET=PingCong

# compiler
CC=$(CROSS)gcc

GTKLIB=`$(CROSS)pkg-config --cflags --libs gtk+-3.0` 

# linker
LD=$(CROSS)gcc
LDFLAGS=$(GTKLIB) -lncurses -ltinfo -lpthread -lcurses

OBJS=	PingCong.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: PingCong.c
	$(CC) -c main.c $(GTKLIB) -o main.o
    
clean:
	rm -f *.o $(TARGET)
