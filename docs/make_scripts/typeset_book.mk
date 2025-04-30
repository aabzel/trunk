
#https://habr.com/ru/companies/ruvds/articles/574352/
#@echo $(error OPT=$(OPT))
FINAL_LATEX_FILE =$(ARTIFACT_NAME).tex
ARTIFACT_DOCS=$(ARTIFACT_NAME).docx
ARTIFACT_PDF=$(ARTIFACT_NAME).pdf


BUILD_DIR=artifacts

#$(error FINAL_LATEX_FILE=$(FINAL_LATEX_FILE))
ifeq ($(ACRONYMS),Y)
#$(error ACRONYMS=$(ACRONYMS))
    EXTRA_PREREQ += sort_acronyms
endif


#CPP_OPT += $(OPT)

PANDOC_OPT += -f latex
PANDOC_OPT += -t docx

include $(DOCUMENTATION_DIR)/library/library.mk
include $(DOCUMENTATION_DIR)/make_scripts/m4_preproc.mk

$(ARTIFACT_DOCS) : $(FINAL_LATEX_FILE) $(BUILD_DIR)
	pandoc -s $^ $(PANDOC_OPT) -o $@


$(ARTIFACT_PDF):  $(FINAL_LATEX_FILE)  $(BUILD_DIR)
	$(info GENERATE_PDF...)
	./latex.bat $(FINAL_LATEX_FILE)

PHONY: move_artifacts
move_artifacts: $(BUILD_DIR) $(ARTIFACT_PDF) $(ARTIFACT_DOCS)
	$(info Move artifacts to $(BUILD_DIR))
	mv $(ARTIFACT_DOCS) $(BUILD_DIR)/$(ARTIFACT_DOCS)
	mv $(ARTIFACT_PDF) $(BUILD_DIR)/$(ARTIFACT_PDF)

PHONY: all
all: $(ARTIFACT_PDF) $(ARTIFACT_DOCS) move_artifacts $(BUILD_DIR)
	$(info All)

$(BUILD_DIR): $(EXTRA_PREREQ)
	$(info build $@ dirr)
	mkdir -p $@

PHONY: clean
clean:
	$(info clean)
	rm $(ART_PDV)
	rm $(FINAL_LATEX_FILE)
	-rm -fR $(BUILD_DIR)

