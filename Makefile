ASM := nasm
ASMFLAGSBIN := -fbin
ASMFLAGSELF := -felf64

OBJCOPY := x86_64-elf-objcopy
OBJCOPYFLAGS := -O binary

LD := x86_64-elf-ld
LDSCRIPT := linker.ld

INCLUDE := include
CC := x86_64-elf-gcc
CCFLAGS := -ffreestanding -I$(INCLUDE) -Wall

BUILD := build

BOOTDIR := boot
KERNELDIR := kernel

KERNEL := $(wildcard $(KERNELDIR)/*.c) \
		  $(wildcard $(KERNELDIR)/interrupt/*.c)
KERNELOBJ := $(patsubst %.c,$(BUILD)/%.o,$(KERNEL))
KERNELELF := $(BUILD)/$(KERNELDIR)/kernel.elf
KERNELBIN := $(KERNELELF:.elf=.bin)

KERNEL_ENTRY := $(KERNELDIR)/kernel.asm
KERNEL_ENTRYOBJ := $(patsubst %.asm,$(BUILD)/%.o,$(KERNEL_ENTRY))

STAGE2 := $(BOOTDIR)/stage2.asm
STAGE2BIN := $(patsubst %.asm,$(BUILD)/%.bin,$(STAGE2))

BOOT := $(BOOTDIR)/boot.asm
BOOTBIN := $(patsubst %.asm,$(BUILD)/%.bin,$(BOOT))

IMAGE := $(BUILD)/os.img

QEMU := qemu-system-x86_64
QEMUFLAGS := -drive format=raw,file=$(IMAGE)

.PHONY: all clean run

run: $(IMAGE)
	$(QEMU) $(QEMUFLAGS)

all: $(IMAGE)

$(KERNELBIN): $(KERNELELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

$(KERNELELF): $(KERNELOBJ) $(LDSCRIPT) $(KERNEL_ENTRYOBJ)
	$(LD) -T $(LDSCRIPT) -o $@ $(KERNELOBJ) $(KERNEL_ENTRYOBJ)

$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

$(BUILD)/%.bin: %.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGSBIN) $< -o $@

$(KERNEL_ENTRYOBJ): $(KERNEL_ENTRY)
	$(ASM) $(ASMFLAGSELF) $< -o $@

$(IMAGE): $(BOOTBIN) $(STAGE2BIN) $(KERNELBIN)
	touch $(IMAGE)
	dd if=$(BOOTBIN) of=$(IMAGE) bs=512 count=1 conv=notrunc
	dd if=$(STAGE2BIN) of=$(IMAGE) seek=1 bs=512 conv=sync,notrunc
	dd if=$(KERNELBIN) of=$(IMAGE) seek=2 bs=512 conv=sync,notrunc

clean:
	rm -rf $(BUILD)
