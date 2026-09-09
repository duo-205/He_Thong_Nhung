TARGET  = nutnhan
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CFLAGS  = -mcpu=cortex-m3 -mthumb -Wall -O2 -ffreestanding -nostdlib
LDFLAGS = -T stm32f103c8t6.ld -nostdlib

SRCS = main.c startup_stm32f103c8t6.s

all: $(TARGET).bin

$(TARGET).elf: $(SRCS) stm32f103c8t6.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(TARGET).elf
	$(SIZE) $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x8000000

clean:
	rm -f *.elf *.bin

.PHONY: all flash clean
