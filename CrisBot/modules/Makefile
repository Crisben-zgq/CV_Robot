MODULES_PATH = $(shell pwd)
MODULES_DEBUG_PATH = $(MODULES_PATH)/modules_debug
CRISBOT_LIBRARY_PATH = $(MODULES_PATH)/../apps/crisbot_libs
MODULES_INCLUDE_PATH = $(MODULES_PATH)/../apps/inc/modules
include $(MODULES_PATH)/../rules.mk


SRCS := $(wildcard $(MODULES_PATH)/*.c)
SRCS += $(wildcard $(MODULES_PATH)/cv/*.c)
SRCS += $(wildcard $(MODULES_PATH)/common/log/*.c)
SRCS += $(wildcard $(MODULES_PATH)/common/xml/*.c)

INCS :=-I$(MODULES_PATH)/common/log
INCS +=-I$(MODULES_PATH)/common/xml
INCS +=-I$(MODULES_PATH)/../apps/inc

CFLAGES += -std=gnu99 -O2 -Wall

OBJ_TMP = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
OBJS = $(patsubst %.o,$(MODULES_DEBUG_PATH)/%.o,$(notdir $(OBJ_TMP)))

vpath %.c $(addsuffix :,$(dir $(OBJ_TMP)))
vpath %.cpp $(addsuffix :,$(dir $(OBJ_TMP)))

MODULES_LIBS = libmodules.a

all:$(MODULES_LIBS)
	cp -f $(MODULES_LIBS) $(CRISBOT_LIBRARY_PATH)
	cp -f $(MODULES_PATH)/common/log/log.h $(MODULES_INCLUDE_PATH)
	cp -f $(MODULES_PATH)/common/xml/xml_api.h $(MODULES_INCLUDE_PATH)


$(MODULES_DEBUG_PATH)/%.o:%.c
	@mkdir -p $(MODULES_DEBUG_PATH)
	@mkdir -p $(MODULES_INCLUDE_PATH)
	$(PRINTF)"CC $<";$(CC) $(CFLAGES) -c $^ -o $@ $(INCS)

$(MODULES_DEBUG_PATH)/%.o:%.cpp
	@mkdir -p $(MODULES_DEBUG_PATH)
	@mkdir -p $(MODULES_INCLUDE_PATH)
	$(PRINTF)"CXX $<";$(CXX) $(CFLAGES) -c $^ -o $@ $(INCS)

$(MODULES_LIBS):$(OBJS)
	$(PRINTF)"LD $@";$(AR) rc $@ $(OBJS)
	$(PRINTF)"RANLIB $@";$(RANLIB) $@


.PHONY:$(MODULES_LIBS)
.PHONY: clean

clean:
	$(PRINTF)"rm modules_debug";rm -rf $(MODULES_DEBUG_PATH)
	$(PRINTF)"rm moduels_libs";rm -rf $(MODULES_LIBS)
	$(PRINTF)"rm moduels_inc";rm -rf $(MODULES_INCLUDE_PATH)
	