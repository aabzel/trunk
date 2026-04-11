# Makefile

include config.mk

TARGET = jz_f407vet6_mbr_light_gcc_m
MCU = cortex-m4
FPU = fpv4-sp-d16
FLOAT_ABI = softfp

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CFLAGS += -mcpu=$(MCU) 
CFLAGS += -mthumb 
CFLAGS += -mfpu=$(FPU) 
CFLAGS += -mfloat-abi=$(FLOAT_ABI)

ifeq ($(DEBUG),Y)
    CFLAGS += -O0
    CFLAGS += -g3 
endif

ifeq ($(PACK_PROGRAM),Y)
    # $(error PACK_PROGRAM=$(PACK_PROGRAM))
    CFLAGS += -Os
    #When compiling with -flto, no callgraph information is output along with
    #the object file.
    #This option runs the standard link-time optimizer.
    #When invoked with source code, it generates GIMPLE (one of GCCs internal representations) and writes
    #it to special ELF sections in the object file.
    # When the object files are linked together, all the function bodies are read 
    # from these ELF sections and instantiated as if they had been part of the same translation unit.
    #COMPILE_GCC_OPT += -flto
endif


CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections 
CFLAGS += -nostdlib 
CFLAGS += -nostartfiles
CFLAGS += -fno-builtin 

CFLAGS += -ffreestanding 
CFLAGS += -fno-exceptions 
CFLAGS += -fno-rtti
CFLAGS += -Wl,-gc-sections -Wl,-s
CFLAGS += -DSTM32F407xx 
CFLAGS += -DUSE_STDPERIPH_DRIVER

# Размещаем код в начале Flash (0x08000000)
LDFLAGS += -mcpu=$(MCU) 
LDFLAGS += -mthumb 
LDFLAGS += -mfpu=$(FPU) 
LDFLAGS += -mfloat-abi=$(FLOAT_ABI)
LDFLAGS += -T gcc_arm_mbr.ld
#LDFLAGS += -nostdlib 
#LDFLAGS += -nostartfiles 
LDFLAGS += -Wl,--print-memory-usage 
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--cref 
#LDFLAGS += -Wl,-Ttext=0x08000000
LDFLAGS += -Wl,-Map=$(TARGET).map
#LDFLAGS += -Wl,--section-start=.text=0x08000000

SOURCES += main.c
SOURCES += system_stm32f4xx.c

OBJECTS += $(SOURCES:.c=.o)
OBJECTS += startup_stm32f407xx.o

all: $(TARGET).bin $(TARGET).hex $(TARGET).elf

$(STARTUP): startup_stm32f407xx.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).bin $(TARGET).hex $(TARGET).map


.PHONY: all clean  

