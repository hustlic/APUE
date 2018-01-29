######################################
#
# File: Makefile
# Makefile for UNIX pratice codes
#
######################################

VPATH = ./

#Targets
COMMON_OBJS += debug.o

1-1_OBJS += 1-1.o
1-2_OBJS += 1-2.o
1-3_OBJS += 1-3.o
1-4_OBJS += 1-4.o
1-6_OBJS += 1-6.o
3-2_OBJS += 3-2.o
3-2-test_trunc_OBJS += 3-2-test_trunc.o
3-ext-1_OBJS += 3-ext-1.o
3-ext-2_OBJS += 3-ext-2.o

1-ext-5_OBJS += 1-ext-5.o
4-1_OBJS += 4-1.o

OBJS += $(COMMON_OBJS) \
		$(1-1_OBJS) \
		$(1-2_OBJS) \
		$(1-3_OBJS) \
		$(1-4_OBJS) \
		$(1-6_OBJS) \
		$(1-ext-5_OBJS) \
		$(3-2-test_trunc_OBJS)\
		$(3-2_OBJS) \
		$(3-ext-1_OBJS) \
		$(3-ext-2_OBJS) \
		$(4-1_OBJS)

all: OUT 1-1 1-2 1-3 1-4 1-6 1-ext-5 \
	 3-2 3-2-test_trunc 3-ext-1 3-ext-2 \
	 4-1

OUT:
	mkdir -p out

1-1: $(1-1_OBJS) $(COMMON_OBJS)
1-2: $(1-2_OBJS) $(COMMON_OBJS)
1-3: $(1-3_OBJS) $(COMMON_OBJS)
1-4: $(1-4_OBJS) $(COMMON_OBJS)
1-6: $(1-6_OBJS) $(COMMON_OBJS)
3-2: $(3-2_OBJS) $(COMMON_OBJS)
3-2-test_trunc: $(3-2-test_trunc_OBJS) $(COMMON_OBJS)
3-ext-1:$(3-ext-1_OBJS) $(COMMON_OBJS)
3-ext-2:$(3-ext-2_OBJS) $(COMMON_OBJS)

1-ext-5: $(1-ext-5_OBJS) $(COMMON_OBJS)
4-1:$(4-1_OBJS) $(COMMON_OBJS)

clean:
	-rm -rf $(OBJS) out

.PHONY:clean out