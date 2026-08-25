
BUILD_DIR := iso/build
BIN_DIR   := iso/bin

GCC_FLAGS := -Isrc -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror
LD_FLAGS  := -T linker.ld -m elf_i386


C_SOURCE   := $(shell find src -type f -name "*.c")
ASM_SOURCE := $(shell find src -type f -name "*.s")

C_OBJECTS   := $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCE))
ASM_OBJECTS := $(patsubst %.s, $(BUILD_DIR)/%.o, $(ASM_SOURCE))

all: clean $(BIN_DIR)/kernel.elf

$(BIN_DIR)/kernel.elf: $(C_OBJECTS) $(ASM_OBJECTS)
	@mkdir -p $(dir $@)
	ld $(LD_FLAGS) $^ -o $@

os.iso: $(BIN_DIR)/kernel.elf
	genisoimage -R 				 \
		    -b boot/grub/stage2_eltorito \
		    -no-emul-boot		 \
		    -boot-load-size 4		 \
		    -A os 			 \
		    -input-charset utf8 	 \
		    -quiet			 \
		    -boot-info-table		 \
		    -o os.iso 			 \
		    iso

run: os.iso
	qemu-system-x86_64 -d int -no-reboot -boot d -cdrom os.iso

clean:
	rm -rf *.o $(BIN_DIR) $(BUILD_DIR)

# GENERIC
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	gcc $(GCC_FLAGS) -c $< -o $@

