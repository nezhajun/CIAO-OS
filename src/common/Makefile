C_INCLUDES = \
-Iinclude

PREFIX := x86_64-elf-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
AR = $(PREFIX)ar
CFLAGS = -g -m32 -MMD -O0 -march=i386 -fno-builtin -fno-omit-frame-pointer -fno-pie -fno-stack-protector -nostdlib -nostdinc -nostartfiles -nodefaultlibs -Werror -Wall -Wno-builtin-declaration-mismatch -Wno-unused-function -Wno-unused-value -Wno-unused-but-set-variable -Wno-unused-variable

CSRC = $(shell find ./ -name "*.c")
SSRC = $(shell find ./ -name "*.S")

START_OBJ = 
OBJS = $(filter-out ./$(START_OBJ), $(SSRC:.S=.o) $(CSRC:.c=.o))
ALL_OBJS = $(START_OBJ) $(OBJS) 

TARGET = libcommon.a

all: $(TARGET) $(ALL_OBJS)

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

libcommon.a: $(ALL_OBJS) Makefile
	$(AR) rcs $@ $(ALL_OBJS)

-include $(ALL_OBJS:.o=.d)

.PHONY: clean
clean:
	rm -f  $(TARGET) $(ALL_OBJS) $(ALL_OBJS:.o=.d)