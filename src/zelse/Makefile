# 工具链前缀，如果是windows和mac，使用x86_64-elf-
# 如果是linux，使用x86_64-linux-gnu-
# 工具链前缀，如果是windows和mac，使用x86_64-elf-
# 如果是linux，使用x86_64-linux-gnu-
# UNAME_S := $(shell uname -s)

# ifeq ($(UNAME_S), Linux)
# 	TOOL_PREFIX = x86_64-linux-gnu-
# else
# 	TOOL_PREFIX = x86_64-elf-
# endif
BUILD_DIR = .build
TOOL_PREFIX = x86_64-elf-


# GCC编译参数
CFLAGS = -g -c -O0 -march=i386 -fno-pie -fno-stack-protector -nostdlib -nostdinc -nostartfiles -nodefaultlibs -Werror -Wall -Wno-builtin-declaration-mismatch -Wno-unused-function -Wno-unused-value -Wno-unused-but-set-variable -Wno-unused-variable
CFLAGS_M16 = $(CFLAGS) -m16
CFLAGS_M32 = $(CFLAGS) -m32
LDFLAGS =  -m elf_i386 

C_INCLUDES = \
-Isrc/common \
-Isrc/boot \
-Isrc/loader \
-Isrc/kernel/init
# 目标创建:涉及编译、链接、二进制转换、反汇编、写磁盘映像
all: $(BUILD_DIR)/start.bin $(BUILD_DIR)/loader.bin $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/start.bin: src/boot/start.S src/boot/boot.c src/boot/boot.h
	@$(info start complier...)
	@echo ****************************************************
	@$(TOOL_PREFIX)gcc $(CFLAGS_M16) $(C_INCLUDES) -o $(BUILD_DIR)/start.o src/boot/start.S
	@$(TOOL_PREFIX)gcc $(CFLAGS_M16) $(C_INCLUDES) -o .build/boot.o src/boot/boot.c
	@$(TOOL_PREFIX)ld $(LDFLAGS) -Ttext=0x7c00 .build/start.o .build/boot.o -o .build/start.elf
	@${TOOL_PREFIX}objcopy -O binary $(BUILD_DIR)/start.elf $(BUILD_DIR)/start.bin
	@${TOOL_PREFIX}size -B $(BUILD_DIR)/start.elf
	@${TOOL_PREFIX}objdump -x -d -S -m i8086 $(BUILD_DIR)/start.elf > $(BUILD_DIR)/start_dis.txt
	@${TOOL_PREFIX}readelf -a  $(BUILD_DIR)/start.elf > $(BUILD_DIR)/start_elf.txt
	@echo ****************************************************

$(BUILD_DIR)/loader.bin: src/loader/loader16.c src/loader/loader16.h src/loader/loader32.c src/loader/loader32.h src/loader/start.S src/common/elf32.c src/common/string.c
	@$(TOOL_PREFIX)gcc $(CFLAGS_M16) $(C_INCLUDES) -o  $(BUILD_DIR)/loader_start.o src/loader/start.S
	@$(TOOL_PREFIX)gcc $(CFLAGS_M16) $(C_INCLUDES) -o $(BUILD_DIR)/loader16.o src/loader/loader16.c
	@$(TOOL_PREFIX)gcc $(CFLAGS_M32) $(C_INCLUDES) -o $(BUILD_DIR)/loader32.o src/loader/loader32.c
	@$(TOOL_PREFIX)gcc $(CFLAGS_M32) $(C_INCLUDES) -o $(BUILD_DIR)/elf32.o src/common/elf32.c
	@$(TOOL_PREFIX)gcc $(CFLAGS_M32) $(C_INCLUDES) -o $(BUILD_DIR)/string.o src/common/string.c
	@$(TOOL_PREFIX)ld $(LDFLAGS) -Ttext=0x8000 $(BUILD_DIR)/loader_start.o $(BUILD_DIR)/loader16.o $(BUILD_DIR)/loader32.o $(BUILD_DIR)/elf32.o $(BUILD_DIR)/string.o -o $(BUILD_DIR)/loader.elf
	@${TOOL_PREFIX}objcopy -O binary $(BUILD_DIR)/loader.elf $(BUILD_DIR)/loader.bin
	@${TOOL_PREFIX}size -B $(BUILD_DIR)/loader.elf
	@${TOOL_PREFIX}objdump -x -d -S -m i8086 $(BUILD_DIR)/loader.elf > $(BUILD_DIR)/loader_dis.txt
	@${TOOL_PREFIX}readelf -a  $(BUILD_DIR)/loader.elf > $(BUILD_DIR)/loader_elf.txt
	@echo ****************************************************

$(BUILD_DIR)/kernel.bin: src/kernel/init/init.c src/kernel/init/start.S $(BUILD_DIR)/string.o
	@$(TOOL_PREFIX)gcc $(CFLAGS_M32) $(C_INCLUDES) -o $(BUILD_DIR)/kernel_start.o src/kernel/init/start.S
	@$(TOOL_PREFIX)gcc $(CFLAGS_M32) $(C_INCLUDES) -o $(BUILD_DIR)/init.o src/kernel/init/init.c
	@$(TOOL_PREFIX)ld $(LDFLAGS) -T src/kernel/kernel.lds $(BUILD_DIR)/kernel_start.o $(BUILD_DIR)/init.o $(BUILD_DIR)/string.o -o $(BUILD_DIR)/kernel.elf
	@${TOOL_PREFIX}objcopy -O binary $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/kernel.bin
	@${TOOL_PREFIX}size -B $(BUILD_DIR)/kernel.elf
	@${TOOL_PREFIX}objdump -x -d -S -m i386 $(BUILD_DIR)/kernel.elf > $(BUILD_DIR)/kernel_dis.txt
	@${TOOL_PREFIX}readelf -a  $(BUILD_DIR)/kernel.elf > $(BUILD_DIR)/kernel_elf.txt
	@echo ****************************************************

	
	@dd if=$(BUILD_DIR)/start.bin of=image/disk.img bs=512 count=1 conv=notrunc
	@dd if=$(BUILD_DIR)/loader.bin of=image/disk.img bs=512 count=32 seek=1 conv=notrunc
	@dd if=$(BUILD_DIR)/kernel.elf of=image/disk.img bs=512 count=500 seek=100 conv=notrunc

.PHONY:gdb clean run

run:
	qemu-system-i386 -m 128M -drive file=image/disk.img,index=0,media=disk,format=raw

# linux 下直接使用如下 make qemu来启动调试程序
gdb:
	qemu-system-i386 -daemonize -m 128M -s -S  -drive file=image/disk.img,index=0,media=disk,format=raw
	gdb --tui -ex "target remote localhost:1234" -ex "set arch i8086" -ex "set print pretty on" -ex "set disassembly-flavor intel" -ex "exec-until *0x7c00" .build/os.elf

# 清理
clean:
#	@del /S /Q .build\\*
	rm -Rf .build/*
