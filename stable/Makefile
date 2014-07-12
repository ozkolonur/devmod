CFLAGS := -c -nostdinc
INC := -I/usr/src/linux/include
CC := i686-pc-linux-gnu-gcc

ifneq ($(V),)
	CFLAGS += -Wall
endif

#all: module utility install
all: subdirs

subdirs:
	make -C ./module
	make -C ./utility

#module:
#	make -C module

#utility:
#	make -C utility

    
clean:
#	make clean -C module
	make clean -C utility


