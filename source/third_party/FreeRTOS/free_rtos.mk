ifneq ($(FREE_FROS_MK_INC),Y)
    FREE_RTOS_MK_INC=Y

    OPT += -DHAS_FREE_RTOS
    OPT += -DHAS_FREERTOS
    OPT += -DHAS_RTOS

    FREE_RTOS_DIR += $(THIRD_PARTY_DIR)/FreeRTOS
    #@echo $(error FREE_RTOS_DIR= $(FREE_RTOS_DIR))
    INCDIR += -I$(FREE_RTOS_DIR)
    INCDIR += -I$(FREE_RTOS_DIR)/Source
    INCDIR += -I$(FREE_RTOS_DIR)/Source/include
    INCDIR += -I$(FREE_RTOS_DIR)/Source/portable
    INCDIR += -I$(FREE_RTOS_DIR)/Source/portable/GCC
    INCDIR += -I$(FREE_RTOS_DIR)/Source/portable/GCC/ARM_CM4F

    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/croutine.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/event_groups.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/list.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/tasks.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/timers.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/queue.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/stream_buffer.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/portable/GCC/ARM_CM4F/port.c
    SOURCES_THIRD_PARTY_C += $(FREE_RTOS_DIR)/Source/portable/MemMang/heap_4.c 
endif