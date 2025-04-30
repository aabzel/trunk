

LINKER_FLAGS +=  --specs=nano.specs
LINKER_FLAGS += -u _scanf_float
LINKER_FLAGS += -u _printf_float

LDFLAGS += $(MCU) -specs=nosys.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections $(LINKER_FLAGS)
