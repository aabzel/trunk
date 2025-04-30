$(info ClangFormatAllScript)

#make clang_format
.PHONY: clang_format
clang_format: clang_format_mcal 
	$(info ClangFormatAllDone)

include $(WORKSPACE_LOC)/make_scripts/clang_format_mcal.mk
#include $(WORKSPACE_LOC)/third_party/clang_format_ehal.mk