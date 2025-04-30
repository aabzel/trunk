ifneq ($(CODE_BASE_PRECONFIG_MK),Y)
    CODE_BASE_PRECONFIG_MK=Y
    $(info CodeBase Pre Config)

    #@echo $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    
    # order matter !
    
    ifeq ($(AUSTERITY_FIRMWARE),Y)
     $(error AUSTERITY_FIRMWARE=$(AUSTERITY_FIRMWARE))
        include $(WORKSPACE_LOC)/make_scripts/austerity_firmware.mk
    endif

    ifeq ($(MODULES),Y)
        #@echo $(error MODULES=$(MODULES))
        include $(WORKSPACE_LOC)/modules/modules_preconfig.mk
    endif

    ifeq ($(BOARD),Y)
        #@echo $(error BOARD=$(BOARD))
        include $(WORKSPACE_LOC)/boards/boards_preconfig.mk
    endif

    ifeq ($(PROTOTYPE),Y)
        #@echo $(error PROTOTYPE=$(PROTOTYPE))
        include $(WORKSPACE_LOC)/prototypes/prototypes_preconfig.mk
    endif

    ifeq ($(ORTHODOX_CANONICAL_FIRMWARE),Y)
        include $(WORKSPACE_LOC)/make_scripts/orthodox_canonical_firmware.mk
    endif
    
    ifeq ($(MICROCONTROLLER),Y)
        FIRMWARE=Y
        #@echo $(error MICROCONTROLLER=$(MICROCONTROLLER))
        include $(WORKSPACE_LOC)/microcontroller/microcontroller_preconfig.mk
    endif

    ifeq ($(THIRD_PARTY),Y)
        #@echo $(error THIRD_PARTY=$(THIRD_PARTY))
        include $(WORKSPACE_LOC)/third_party/third_party_preconfig.mk
    endif

    ifeq ($(CORE),Y)
        #@echo $(error CORE=$(CORE))
        include $(WORKSPACE_LOC)/core/core_preconfig.mk
    endif

    ifeq ($(APPLICATIONS),Y)
        #@echo $(error APPLICATIONS=$(APPLICATIONS))
        include $(WORKSPACE_LOC)/applications/applications_preconfig.mk
    endif

    ifeq ($(MCAL),Y)
        #@echo $(error MCAL=$(MCAL))
        include $(WORKSPACE_LOC)/mcal/mcal_preconfig.mk
    endif

    ifeq ($(ADT),Y)
        #@echo $(error ADT=$(ADT))
        include $(WORKSPACE_LOC)/adt/adt_preconfig.mk
    endif

    ifeq ($(CONNECTIVITY),Y)
        #@echo $(error CONNECTIVITY=$(CONNECTIVITY))
        include $(WORKSPACE_LOC)/connectivity/connectivity_preconfig.mk
    endif
    
    ifeq ($(COMPONENTS),Y)
        #@echo $(error COMPONENTS=$(COMPONENTS))
        include $(WORKSPACE_LOC)/components/components_preconfig.mk
    endif

    ifeq ($(COMPUTING),Y)
        #@echo $(error COMPUTING=$(COMPUTING))
        include $(WORKSPACE_LOC)/computing/computing_preconfig.mk
    endif

    ifeq ($(MCAL),Y)
        #@echo $(error MCAL=$(MCAL))
        include $(WORKSPACE_LOC)/mcal/mcal_preconfig.mk
    endif

    ifeq ($(SENSITIVITY),Y)
        #@echo $(error SENSITIVITY=$(SENSITIVITY))
        include $(WORKSPACE_LOC)/sensitivity/sensitivity_preconfig.mk
    endif

    ifeq ($(STORAGE),Y)
        #@echo $(error STORAGE=$(STORAGE))
        include $(WORKSPACE_LOC)/storage/storage_preconfig.mk
    endif

    ifeq ($(SECURITY),Y)
        #@echo $(error SECURITY=$(SECURITY))
        include $(WORKSPACE_LOC)/security/security_preconfig.mk
    endif

    ifeq ($(COMMON),Y)
        #@echo $(error COMMON=$(COMMON))
        include $(WORKSPACE_LOC)/common/common_preconfig.mk
    endif

    ifeq ($(ASICS),Y)  
        include $(WORKSPACE_LOC)/asics/asics_preconfig.mk
    endif
    
    ifeq ($(UNIT_TEST),Y)  
        include $(WORKSPACE_LOC)/unit_tests/unit_test_preconfig.mk
    endif

    ifeq ($(MISCELLANEOUS),Y)
        include $(WORKSPACE_LOC)/miscellaneous/miscellaneous_preconfig.mk
    endif

    ifeq ($(THIRD_PARTY),Y)
        #@echo $(error THIRD_PARTY=$(THIRD_PARTY))
        include $(WORKSPACE_LOC)/third_party/third_party_preconfig.mk
    endif
    
    ifeq ($(SOLUTIONS),Y)
        include $(WORKSPACE_LOC)/solutions/solutions_preconfig.mk
    endif

    ifeq ($(LEET_CODE),Y)
        include $(WORKSPACE_LOC)/leet_code/leet_code_preconfig.mk
    endif

    ifeq ($(CONTROL),Y)
        #@echo $(error CONTROL=$(CONTROL))
        include $(WORKSPACE_LOC)/control/control_preconfig.mk
    endif
endif