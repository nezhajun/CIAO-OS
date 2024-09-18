C_INCLUDES = \
-Iinit \
-I../common/include \
-Iinclude/init \
-Iinclude/fs \
-Iinclude/dev \
-Iinclude/test \
-Iinclude/task \
-Iinclude/ipc

PREFIX := x86_64-elf-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
CFLAGS = -g -m32 -MMD -O0 -march=i386 -fno-builtin \
-fno-omit-frame-pointer -fno-pie -fno-stack-protector \
-nostdlib -nostdinc -nostartfiles -nodefaultlibs -Werror -Wall \
-Wno-builtin-declaration-mismatch -Wno-unused-function -Wno-unused-value \
-Wno-unused-but-set-variable -Wno-unused-variable -Wno-div-by-zero

LDFLAGS = -m elf_i386 -T kernel.lds
#LDFLAGS = -Ttext=0xc0030000 -m elf_i386 

CSRC = $(shell find ./ -name "*.c")
SSRC = $(shell find ./ -name "*.S")


LIBS = ../common/libcommon.a
START_OBJ = init/start.o
OBJS = $(filter-out ./$(START_OBJ), $(SSRC:.S=.o) $(CSRC:.c=.o))
ALL_OBJS = $(START_OBJ) $(OBJS) 

TARGET = kernel.bin kernel.elf kernel_dis kernel_readelf

all: $(TARGET)

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

kernel.elf: $(ALL_OBJS) Makefile
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS) $(LIBS)
	$(PREFIX)size -B $@

kernel.bin: kernel.elf
	$(PREFIX)objcopy -S -O binary $< $@

kernel_dis: kernel.elf
	$(PREFIX)objdump -x -d -S -m i386 $< > $@

kernel_readelf: kernel.elf
	$(PREFIX)readelf -a $< > $@

-include $(ALL_OBJS:.o=.d)

.PHONY: clean
clean:
	-rm -f  $(TARGET) $(ALL_OBJS) $(ALL_OBJS:.o=.d)