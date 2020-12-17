# change application name here (executable output name)
TARGET=PingCong

# compiler
CC=$(CROSS)gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

AR=$(CROSS)ar

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe -fno-exceptions -ffunction-sections -fdata-sections -flto

GTKLIB=`$(CROSS)pkg-config --cflags --libs gtk+-3.0` 

# linker
LD=$(CROSS)gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -lncurses -ltinfo -lpthread -lcurses

OBJS=	PingCong.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: PingCong.c
	$(CC) -c $(CCFLAGS) main.c $(GTKLIB) -o main.o
    
clean:
	rm -f *.o $(TARGET)
