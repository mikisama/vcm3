CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc

QEMU ?= qemu-system-arm
RENODE ?= renode
BUILD := build
ELF := $(BUILD)/hello.elf
OBJS := $(BUILD)/startup.o $(BUILD)/main.o

CPUFLAGS := -mcpu=cortex-m3 -mthumb
CFLAGS := $(CPUFLAGS) -O0 -g3 -Wall -Wextra -ffunction-sections -fdata-sections
LDFLAGS := $(CPUFLAGS) -T linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD)/hello.map --specs=rdimon.specs

.PHONY: all run clean

all: $(ELF)

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS) linker.ld
	$(CC) $(LDFLAGS) $(OBJS) -o $@

run_qemu: $(ELF)
	@echo "press CTRL-A than X to exit"
	@$(QEMU) -M mps2-an385 -nographic -semihosting -kernel $(ELF) || true

run_renode: $(ELF)
	@echo "press CTRL-C to exit"
	@$(RENODE) --disable-gui stage1.resc -e "start"

gdbserver_renode: $(ELF)
	@$(RENODE) --disable-gui stage1.resc

# "-s" is short to "-gdb tcp::1234"
gdbserver_qemu: $(ELF)
	@$(QEMU) -M mps2-an385 -nographic -semihosting -kernel $(ELF) -S -gdb tcp::3333 || true

# gdbserver must be started
gdbclient:
	arm-none-eabi-gdb $(ELF) -ex "target remote :3333"

clean:
	rm -rf $(BUILD)
