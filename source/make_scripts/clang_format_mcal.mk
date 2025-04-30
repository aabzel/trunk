$(info ClangFormatScript)

CLANG_FORMAT_TOOL =C:/cygwin64/bin/clang-format.exe
SOURCES_CFM := $(subst .c,.cfm, $(SOURCES_C))

#$(error SOURCES_CFM=$(SOURCES_CFM))

MCAL_STYLE="{
MCAL_STYLE+= BreakBeforeBraces: Attach,
MCAL_STYLE+= ColumnLimit: 120,
MCAL_STYLE+= IndentWidth: 4,
MCAL_STYLE+= PointerAlignment: Left,
MCAL_STYLE+= SortUsingDeclarations: true,
MCAL_STYLE+= SpaceBeforeParens: Never,
MCAL_STYLE+= SortIncludes: true,
MCAL_STYLE+= TabWidth: 4,
MCAL_STYLE+= UseTab: Never,
MCAL_STYLE+=}"
#$(error MCAL_STYLE=$(MCAL_STYLE))

.PHONY: %.cfm
%.cfm: %.c
	$(info RunClangFormat)
	$(CLANG_FORMAT_TOOL) -verbose -i -style=$(MCAL_STYLE) $<

# make -i clang_format_mcal
.PHONY: clang_format_mcal
clang_format_mcal: $(SOURCES_CFM)
	$(info ClangFormatDone)

