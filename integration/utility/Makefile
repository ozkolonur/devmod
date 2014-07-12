CFLAGS :=
INC := -I.
CC := i686-pc-linux-gnu-gcc

ifneq ($(V),)
	CFLAGS += -Wall
endif

all: devmod

devmod: devmod.c
#	echo $(CC) $(CFLAGS) $(INC)
	$(CC) $(CFLAGS) $(INC) -o devmod devmod.c 
    
clean:
	rm -f devmod

