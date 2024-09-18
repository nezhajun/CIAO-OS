C_INCLUDES = \
-Iinclude \
-I../common/include


PREFIX := x86_64-elf-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
CFLAGS = -g -MMD -O0 -march=i386 -fno-builtin -fno-omit-frame-pointer -fno-pie -fno-stack-protector -nostdlib -nostdinc -nostartfiles -nodefaultlibs -Werror -Wall -Wno-builtin-declaration-mismatch -Wno-unused-function -Wno-unused-value -Wno-unused-but-set-variable -Wno-unused-variable
LDFLAGS = -Ttext=0x8000 -m elf_i386
#LDFLAGS = -Ttext=0xc0030000 -m elf_i386 

CSRC = $(shell find ./ -name "*.c") $(LIB_CSRC)
SSRC = $(shell find ./ -name "*.S")


LIBS =	../common/libcommon.a
START_OBJ = start.o
OBJS = $(filter-out ./$(START_OBJ), $(SSRC:.S=.o) $(CSRC:.c=.o))
ALL_OBJS = $(START_OBJ) $(OBJS)

TARGET = loader.bin loader.elf loader_dis loader_readelf

all: $(TARGET)

start.o: start.S
	$(CC) $(CFLAGS) -m16 -c $< -o $@

loader16.o: loader16.c
	$(CC) $(CFLAGS) -m16 $(C_INCLUDES) -c $< -o $@

loader32.o: loader32.c
	$(CC) $(CFLAGS) -m32 $(C_INCLUDES) -c $< -o $@

../common/src/elf32.o: ../common/src/elf32.c
	$(CC) $(CFLAGS) -m32 $(C_INCLUDES) -c $< -o $@

../common/src/string.o: ../common/src/string.c
	$(CC) $(CFLAGS) -m32 $(C_INCLUDES) -c $< -o $@

loader.elf: $(ALL_OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@  $(ALL_OBJS) $(LIBS)
	$(PREFIX)size -B $@

loader.bin: loader.elf
	$(PREFIX)objcopy -S -O binary $< $@

loader_dis: loader.elf
	$(PREFIX)objdump -x -d -S -m i386 $< > $@

loader_readelf: loader.elf
	$(PREFIX)readelf -a $< > $@

-include $(ALL_OBJS:.o=.d)

.PHONY: clean test
clean:
	-rm -f  $(TARGET) $(ALL_OBJS) $(ALL_OBJS:.o=.d)

test:
	echo $(START_OBJ)
	echo $(OBJS)