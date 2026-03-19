ifneq ($(CODE_BASE_MK),Y)
    CODE_BASE_MK=Y
    $(info CodeBase Config)
    #AUTO_INIT=Y
    #AUTO_VERSION_BUILD=Y
    #DEPENDENCIES_GRAPHVIZ=Y

    WORKSPACE_LOC:=$(realpath $(WORKSPACE_LOC))
    WORKSPACE_LOC:=$(subst /cygdrive/c/,C:/,$(WORKSPACE_LOC))
    # $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    include $(WORKSPACE_LOC)/make_scripts/code_base_preconfig.mk
    include $(WORKSPACE_LOC)/make_scripts/verify_build.mk

    # $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    INCDIR += -I$(WORKSPACE_LOC)
    $(info WORKSPACE_LOC=$(WORKSPACE_LOC))

    GIT_SHA := $(shell git rev-parse --short HEAD)
    MCAL_OPT += -DGIT_SHA=0x0$(GIT_SHA)
    MCAL_OPT += -DHAS_MAKEFILE_BUILD

    ifeq ($(START_PAUSE),Y)
        MCAL_OPT += -DHAS_START_PAUSE
    endif

    ifeq ($(NORTOS),Y)
        MCAL_OPT += -DHAS_NORTOS
    endif

    ifeq ($(MULTIMEDIA),Y)
        # $(error MULTIMEDIA=$(MULTIMEDIA))
        MCAL_OPT += -DHAS_MULTIMEDIA
    endif

    ifeq ($(DEBUG),Y)
        MCAL_OPT += -DHAS_DEBUG
    endif

    ifeq ($(DIAG),Y)
        MCAL_OPT += -DHAS_DIAG
    endif

    include $(WORKSPACE_LOC)/Include/Include.mk

    ifeq ($(MODULES),Y)
        # $(error MODULES=$(MODULES))
        include $(WORKSPACE_LOC)/modules/modules.mk
    endif

    ifeq ($(TERMINAL),Y)
        include $(WORKSPACE_LOC)/make_scripts/terminal.mk
    endif

    ifeq ($(GENERIC),Y)
        include $(WORKSPACE_LOC)/make_scripts/generic.mk
    endif

    ifeq ($(NRF5340),Y)
        # $(error NRF5340=$(NRF5340))
        include $(WORKSPACE_LOC)/make_scripts/nrf5340_preconfig.mk
    endif

    #presets done
    ifeq ($(EHAL),Y)
        include $(WORKSPACE_LOC)/Include/Include.mk
    endif

    ifeq ($(MICROCONTROLLER),Y)
        FIRMWARE=Y
        # $(error MICROCONTROLLER=$(MICROCONTROLLER))
        include $(WORKSPACE_LOC)/microcontroller/microcontroller.mk
    endif

    ifeq ($(BOARD),Y)
        # $(error BOARD=$(BOARD))
        include $(WORKSPACE_LOC)/boards/boards.mk
    endif

    ifeq ($(PROTOTYPE),Y)
        # $(error PROTOTYPE=$(PROTOTYPE))
        include $(WORKSPACE_LOC)/prototypes/prototypes.mk
    endif


    # $(error TIME=$(TIME))


    #  @echo $(error UART=$(UART))

    ifeq ($(X86),Y)
        MCAL_OPT += -DX86
        MCAL_OPT += -DHAS_X86
        FLOAT_UTILS=Y
    endif

    ifeq ($(X86_64),Y)
        # $(error stop)
        MCAL_OPT += -DX86_64
        MCAL_OPT += -DHAS_X86_64
    endif

    ifeq ($(THIRD_PARTY),Y)
        # $(error THIRD_PARTY=$(THIRD_PARTY))
        include $(WORKSPACE_LOC)/third_party/third_party.mk
    endif

    ifeq ($(CORE),Y)
        # $(error CORE=$(CORE))
        include $(WORKSPACE_LOC)/core/core.mk
    endif

    ifeq ($(APPLICATIONS),Y)
        # $(error APPLICATIONS=$(APPLICATIONS))
        include $(WORKSPACE_LOC)/applications/applications.mk
    endif

    ifeq ($(GAMES),Y)
        # $(error GAMES=$(GAMES))
        include $(WORKSPACE_LOC)/games/games.mk
    endif

    ifeq ($(MCAL),Y)
        # $(error MCAL=$(MCAL))
        include $(WORKSPACE_LOC)/mcal/mcal.mk
    endif

    ifeq ($(ADT),Y)
        # $(error ADT=$(ADT))
        include $(WORKSPACE_LOC)/adt/adt.mk
    endif

    ifeq ($(CONNECTIVITY),Y)
        # $(error CONNECTIVITY=$(CONNECTIVITY))
        include $(WORKSPACE_LOC)/connectivity/connectivity.mk
    endif

    ifeq ($(CONTROL),Y)
        # $(error CONTROL=$(CONTROL))
        include $(WORKSPACE_LOC)/control/control.mk
    endif
    
    ifeq ($(COMPONENTS),Y)
        # $(error COMPONENTS=$(COMPONENTS))
        include $(WORKSPACE_LOC)/components/components.mk
    endif

    ifeq ($(COMPUTING),Y)
        # $(error COMPUTING=$(COMPUTING))
        include $(WORKSPACE_LOC)/computing/computing.mk
    endif

    include $(WORKSPACE_LOC)/compiler/compiler.mk
        
    ifeq ($(SENSITIVITY),Y)
        # $(error SENSITIVITY=$(SENSITIVITY))
        include $(WORKSPACE_LOC)/sensitivity/sensitivity.mk
    endif

    ifeq ($(STORAGE),Y)
        # $(error STORAGE=$(STORAGE))
        include $(WORKSPACE_LOC)/storage/storage.mk
    endif

    ifeq ($(SECURITY),Y)
        # $(error SECURITY=$(SECURITY))
        include $(WORKSPACE_LOC)/security/security.mk
    endif

    ifeq ($(ASICS),Y)
        include $(WORKSPACE_LOC)/asics/asics.mk
    endif

    ifeq ($(COMMON),Y)
        # $(error COMMON=$(COMMON))
        include $(WORKSPACE_LOC)/common/common.mk
    endif

    ifeq ($(MISCELLANEOUS),Y)
        include $(WORKSPACE_LOC)/miscellaneous/miscellaneous.mk
    endif

    ifeq ($(UNIT_TEST),Y)  
        include $(WORKSPACE_LOC)/unit_tests/unit_test.mk
    endif

    ifeq ($(SOLUTIONS),Y)
        include $(WORKSPACE_LOC)/solutions/solutions.mk
    endif

    ifeq ($(LEET_CODE),Y)
        include $(WORKSPACE_LOC)/leet_code/leet_code.mk
    endif

    ifneq ($(MAIN_CUSTOM),Y)
        # $(error FIRMWARE=$(FIRMWARE))
        SOURCES_C += $(WORKSPACE_LOC)/main.c
    endif
endif