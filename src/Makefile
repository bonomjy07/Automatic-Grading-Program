############## SunOS ########################
CC       = gcc -g
CCOPTS   = -c #-Wall
LINK     = gcc -g
LDFLAGS  = -pthread

TARGET   = grading

DEPEND   = makedepend

LINKOPTS = -lm 
#LINKOPTS = -lm -lnsl # Doesn't work on MacOs
#############################################

SOURCES = grading.c test.c answer.c color.c

OBJECTS = grading.o test.o answer.o color.o

.SUFFIXES : .C .c .o

.c.o:
	$(CC) $(CCOPTS) $<

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK) -o $(TARGET) $(OBJECTS) $(LINKOPTS) $(LDFLAGS)

clean:
	rm *.o
	rm ./$(TARGET)

depend : $(SOURCES)
	$(DEPEND) $(DEFINES) -I/usr/local/lib/g++-include $(SOURCES)

hello:
	echo hello!
