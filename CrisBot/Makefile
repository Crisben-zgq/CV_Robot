LOCAL_PATH = $(shell pwd)
First_DEBUG = modules
CRISBOT_DEBUG = $(First_DEBUG)
CRISBOT_DEBUG += apps
include $(LOCAL_PATH)/rules.mk

all:$(CRISBOT_DEBUG)
	@for debug in $(CRISBOT_DEBUG); \
    	do \
    		if [ -e $$debug/Makefile ]; then make -C $$debug; fi \
    	done
	$(PRINTF)"make CRISBOT_DEBUG end"


clean:
	@for debug in $(CRISBOT_DEBUG); \
    	do \
    		if [ -e $$debug/Makefile ]; then make -C $$debug clean; fi \
    	done