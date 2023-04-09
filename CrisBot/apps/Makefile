APPS_PATH = $(shell pwd)
CRISBOT_PATH = $(APPS_PATH)/../crisbot
APPS_DEBUG_PATH = $(APPS_PATH)/apps_debug
include $(APPS_PATH)/../rules.mk



SRCS := $(wildcard $(APPS_PATH)/*.c)
SRCS += $(wildcard $(APPS_PATH)/src/default_config_info/*.c)
SRCS += $(wildcard $(APPS_PATH)/src/hardware_info/*.c)

INCS :=-I$(APPS_PATH)/inc
INCS +=-I$(APPS_PATH)/src/default_config_info
INCS +=-I$(APPS_PATH)/src/hardware_info
INCS +=-I$(APPS_PATH)/inc/modules

CFLAGES += -std=gnu99 -O2 -Wall
LDFLAGES += -lstdc++ -lpthread  -lm -lrt -ldl
LIBS_PATH := -L$(APPS_PATH)/crisbot_libs 
LDFLAGES += $(LIBS_PATH)
LDFLAGES += -lmodules
LDFLAGES += -lmxml

OBJ_TMP = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
OBJS = $(patsubst %.o,$(APPS_DEBUG_PATH)/%.o,$(notdir $(OBJ_TMP)))

vpath %.c $(addsuffix :,$(dir $(OBJ_TMP)))
vpath %.cpp $(addsuffix :,$(dir $(OBJ_TMP)))

TARGET = crisbot
TARGET_SQF = crisbot.squashfs

all:$(CRISBOT_PATH)/$(TARGET)


$(APPS_DEBUG_PATH)/%.o:%.c
	@mkdir -p $(APPS_DEBUG_PATH)
	$(PRINTF)"CC $<";$(CC) $(CFLAGES) -c $^ -o $@ $(INCS)

$(APPS_DEBUG_PATH)/%.o:%.cpp
	@mkdir -p $(APPS_DEBUG_PATH)
	$(PRINTF)"CXX $<";$(CXX) $(CFLAGES) -c $^ -o $@ $(INCS)

$(CRISBOT_PATH)/$(TARGET):$(OBJS)
	$(PRINTF)"LD $@";$(CC) $(CFLAGES) $(OBJS) -Xlinker "-(" $(LDFLAGES) -Xlinker "-)" -o $@
	$(STRIP) $(CRISBOT_PATH)/$(TARGET)
	mksquashfs $(CRISBOT_PATH)/$(TARGET) $(CRISBOT_PATH)/$(TARGET_SQF) -comp xz

.PHONY:$(CRISBOT_PATH)/$(TARGET)
.PHONY: clean

clean:
	$(PRINTF)"rm apps_debug";rm -rf $(APPS_DEBUG_PATH)
	$(PRINTF)"rm crisbot";rm -rf $(CRISBOT_PATH)/$(TARGET)
	$(PRINTF)"rm crisbot.squashfs";rm -rf $(CRISBOT_PATH)/$(TARGET_SQF)

