$(info run m4 - macro processor script)

# --traditional  suppress all GNU extensions
#M4_MACRO_OPT +=-G # cause include error 


M4_MACRO_OPT +=-i
M4_MACRO_OPT += $(MACRO_OPT)

#$(info before change INC_DIR=$(INCDIR))
#INCLUDE_PATHS:=$(subst /,\,$(INCLUDE_PATHS))
#$(info after change INCLUDE_PATHS=$(INCLUDE_PATHS))

#INCDIR:=$(subst \,/,$(INCDIR))
#INCLUDE_PATHS:=$(subst /,\,$(INCLUDE_PATHS))
#INCLUDE_PATHS:=$(subst -I,--include=,$(INCLUDE_PATHS))

M4_OPT += $(INCLUDE_PATHS)
M4_OPT += $(M4_MACRO_OPT)

EXTRA_PREREQ +=
    
$(FINAL_LATEX_FILE): $(BUILD_DIR) $(EXTRA_PREREQ)
	$(info run m4 - macro processor...To obtain $@)
	m4  $(M4_OPT) main.texi > $(FINAL_LATEX_FILE)

