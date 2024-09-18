C_INCLUDES = \
-I. \
-I../common/include

LIB_CSRC =


PREFIX := x86_64-elf-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
CFLAGS = -g -MMD -O0 -march=i386 -fno-builtin -fno-omit-frame-pointer -fno-pie -fno-stack-protector -nostdlib -nostdinc -nostartfiles -nodefaultlibs -Werror -Wall -Wno-builtin-declaration-mismatch -Wno-unused-function -Wno-unused-value -Wno-unused-but-set-variable -Wno-unused-variable
LDFLAGS = -Ttext=0x7c00 -m elf_i386
#LDFLAGS = -Ttext=0xc0030000 -m elf_i386 

CSRC = $(shell find ./ -name "*.c") $(LIB_CSRC)
SSRC = $(shell find ./ -name "*.S")

LIBS =
START_OBJ = start.o
OBJS = $(filter-out ./$(START_OBJ), $(SSRC:.S=.o) $(CSRC:.c=.o))
ALL_OBJS = $(START_OBJ) $(OBJS)

TARGET = boot.bin boot.elf boot_dis boot_readelf

all: $(TARGET)

%.o: %.S
	$(CC) $(CFLAGS) -m16 -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -m16 $(C_INCLUDES) -c $< -o $@


boot.elf: $(ALL_OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@  $(ALL_OBJS)
	$(PREFIX)size -B $@

boot.bin: boot.elf
	$(PREFIX)objcopy -S -O binary $< $@

boot_dis: boot.elf
	$(PREFIX)objdump -x -d -S -m i386 $< > $@

boot_readelf: boot.elf
	$(PREFIX)readelf -a $< > $@

-include $(ALL_OBJS:.o=.d)

.PHONY: clean test
clean:
	-rm -f  $(TARGET) $(ALL_OBJS) $(ALL_OBJS:.o=.d)

test:
	echo $(START_OBJ)
	echo $(OBJS)