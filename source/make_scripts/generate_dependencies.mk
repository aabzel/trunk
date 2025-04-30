#CC=C:/cygwin64/bin/dot.exe
$(info Generate Dependencies)

CC_DOT="C:/Program Files/Graphviz/bin/dot.exe"
RENDER="C:/Program Files/Google/Chrome/Application/chrome.exe"

$(info MK_PATH=$(MK_PATH))
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))
$(info MK_PATH_WIN=$(MK_PATH_WIN))

$(info WORKSPACE_LOC=$(WORKSPACE_LOC))
ARTEFACTS_DIR=$(MK_PATH_WIN)/$(BUILD_DIR)

$(info ARTEFACTS_DIR=$(ARTEFACTS_DIR))
#RENDER=chrome.exe
#CURRENT_DIR = $(shell pwd)
#$(info CURRENT_DIR=$(CURRENT_DIR) )
#WORKSPACE_LOC:=$(CURRENT_DIR)/../

#CURRENT_DIR := $(subst /cygdrive/c/,C:/, $(CURRENT_DIR))
#CURRENT_DIR := $(subst /c/,C:/, $(CURRENT_DIR))

#WORKSPACE_LOC := $(subst /cygdrive/c/,C:/, $(WORKSPACE_LOC))
#WORKSPACE_LOC := $(subst /c/,C:/, $(WORKSPACE_LOC))

#$(info CURRENT_DIR=$(CURRENT_DIR) )

SOURCES_DOT=$(WORKSPACE_LOC)/main.gvi

$(info SOURCES_DOT=$(SOURCES_DOT))
SOURCES_DOT:=$(subst /cygdrive/c/,C:/, $(SOURCES_DOT))
$(info SOURCES_DOT=$(SOURCES_DOT))

SOURCES_DOT_RES += $(ARTEFACTS_DIR)/$(TARGET)_dep.gv
$(info SOURCES_DOT_RES=$(SOURCES_DOT_RES))

ART_SVG = $(ARTEFACTS_DIR)/$(TARGET)_res.svg
ART_PDF = $(ARTEFACTS_DIR)/$(TARGET)_res.pdf

$(info ART_SVG=$(ART_SVG) )
$(info ART_PDF=$(ART_PDF) )

CPP_GV_OPT += -undef
CPP_GV_OPT += -P
CPP_GV_OPT += -E
CPP_GV_OPT += -nostdinc

CPP_GV_OPT += $(OPT)

#DOT_OPT +=-L10
#DOT_OPT +=-v 
#LAYOUT_ENGINE = -Kneato 
#LAYOUT_ENGINE = -Kfdp 
#LAYOUT_ENGINE = -Ksfdp
#LAYOUT_ENGINE = -Ktwopi
#LAYOUT_ENGINE = -Kosage
#LAYOUT_ENGINE = -Kpatchwork
LAYOUT_ENGINE = -Kdot
#DEPENDENCY_GRAPH += generate_dep

.PHONY: preproc_graphviz

preproc_graphviz: $(SOURCES_DOT) $(ARTIFACTS) sort_config
	$(info Preproc...)
	mkdir -p $(ARTEFACTS_DIR)
	$(PREPROCESSOR_TOOL) $(SOURCES_DOT)  $(CPP_GV_OPT) $(INCDIR) -E -o $(SOURCES_DOT_RES)

.PHONY: generate_dep_jpeg

generate_dep_jpeg: preproc_graphviz
	$(info route graph...)
	$(CC_DOT) -V
	$(CC_DOT) -Tjpeg $(LAYOUT_ENGINE) $(SOURCES_DOT_RES) -o $(ARTEFACTS_DIR)/$(TARGET).jpeg

.PHONY: generate_dep_pdf

generate_dep_pdf: preproc_graphviz
	$(info route graph...)
	$(CC_DOT) -V
	$(CC_DOT) -Tpdf $(LAYOUT_ENGINE) $(SOURCES_DOT_RES) -o $(ARTEFACTS_DIR)/$(TARGET).pdf

.PHONY: generate_dep_svg

generate_dep_svg: preproc_graphviz
	$(info route graph...)
	$(CC_DOT) -V
	$(CC_DOT) -Tsvg $(SOURCES_DOT_RES) -o $(ARTEFACTS_DIR)/$(TARGET).svg

.PHONY: generate_dep

generate_dep: generate_dep_svg generate_dep_pdf generate_dep_jpeg
	$(info generate_dep done)

.PHONY: print_dep

print_dep: generate_dep
	$(info print_svg)
	$(RENDER) -open $(ARTEFACTS_DIR)/$(TARGET).svg
	$(RENDER) -open $(ARTEFACTS_DIR)/$(TARGET).pdf

#clean:
#	$(info clean)
#	rm $(MK_PATH)/artefacts/*.*


#$(ART_SVG):$(ART_SVG)

