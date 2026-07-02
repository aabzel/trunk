ifneq ($(WAV_PRECONFIG_INC),Y)
    WAV_PRECONFIG_INC=Y

    #@ echo $(error WAV_DIR = $(WAV_DIR))
    ARRAY=Y
    WAV=Y
    CSV=Y
    STORAGE=Y
    DDS=Y
endif

 

