

CPP_OPT += -undef

# If you request textual output from the preprocessor with the -E option, it will be in UTF-8.
CPP_OPT += -E

# Inhibit generation of linemarkers in the output from the preprocessor. 
# This might be useful when running the preprocessor on something that is not C code,
# and will be sent to a program which might be confused by the linemarkers.
CPP_OPT += -P

#Do not discard comments. All comments are passed through to the output file, 
#except for comments in processed directives, which are deleted along with the directive.
#You should be prepared for side effects when using -C; it causes the 
#preprocessor to treat comments as tokens in their own right. 
#For example, comments appearing at the start of what would be a directive line 
#have the effect of turning that line into an ordinary source line, since 
#the first token on the line is no longer a #.
CPP_OPT += -C

CPP_OPT += -fexec-charset=UTF-8

# Traditional Mode Try to imitate the behavior of old-fashioned C, as opposed to ISO C.
CPP_OPT += -traditional-cpp


#Do not search the standard system directories for header files. 
#Only the directories you have specified with -I options (and the directory of 
#the current file, if appropriate) are searched.
CPP_OPT += -nostdinc

cpp_preproc:$(SOURCES_TEXI)
	$(info run cpp - macro processor...)
	cpp main.texi  $(CPP_OPT) $(INCLUDE_PATHS) > $@


