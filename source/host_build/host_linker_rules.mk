

# On systems that support dynamic linking, this overrides вЂ�-pieвЂ™ and prevents
# linking with the shared libraries. On other systems, this option has no effect
LFLAGS += -static

#The m stands for libm, the library that contains <math.h>
#math.h is not a part of the standard C library, so you have to link to it!
LFLAGS += -lm
LFLAGS += -O0

# Add standard C library
#LFLAGS += -lc

#@echo $(error LFLAGS= $(LFLAGS))
#@echo $(error CFLAGS= $(CFLAGS))
#@echo $(error TARGET= $(TARGET))
#@echo $(error CC= $(CC))
#@echo $(info OBJECTS= $(OBJECTS))

$(TARGET):  $(OBJECTS) 
	@echo RunLinker...
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET).exe
	#$(SZ) $(TARGET).exe



