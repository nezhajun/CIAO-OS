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
TOOL_PREFIX = x86_64-elf-

.PHONY: kernel boot loader debug clean
# 目标创建:涉及编译、链接、二进制转换、反汇编、写磁盘映像
all:
	cd src/common && make
	cd src/boot && make && \
	dd if=boot.bin of=../../image/disk.img bs=512 count=1 conv=notrunc
	cd src/loader && make && \
	dd if=loader.bin of=../../image/disk.img bs=512 count=32 seek=1 conv=notrunc
	cd src/kernel && make && \
	dd if=kernel.elf of=../../image/disk.img bs=512 count=500 seek=100 conv=notrunc
	@echo successfully compiled...

kernel:
	cd src/kernel && make

run:
	qemu-system-i386 -m 128M -nographic -drive file=image/disk.img,index=0,media=disk,format=raw

# linux 下直接使用如下 make qemu来启动调试程序
debug:
	qemu-system-i386 -daemonize -m 128M -s -S  -drive file=image/disk.img,index=0,media=disk,format=raw
	gdb --tui -ex "target remote localhost:1234" -ex "set arch i8086" -ex "set print pretty on" -ex "set disassembly-flavor intel" -ex "exec-until *0x7c00" .build/os.elf

clean:
	cd src/boot && make clean
	cd src/common && make clean
	cd src/loader && make clean
	cd src/kernel && make clean
