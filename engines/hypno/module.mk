MODULE := engines/hypno

MODULE_OBJS := \
	cursors.o \
	metaengine.o \
	lexer.o \
	grammar.o \
	hypno.o

MODULE_DIRS += \
	engines/hypno

# HACK: Skip this when including the file for detection objects.
ifeq "$(USE_RULES)" "1"
hypno-grammar:
	flex engines/hypno/lexer.l
	bison engines/hypno/grammar.y
endif

# This module can be built as a plugin
ifeq ($(ENABLE_HYPNO), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o
