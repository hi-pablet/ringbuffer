################################################################################
# Source files
################################################################################

LIB			 := bin/ringbuffer.a
LIB_SRC      := ringbuffer.c
LIB_OBJ      := $(addprefix obj/,$(notdir $(LIB_SRC:.c=.o)))

MAIN     	 := bin/ringbuff
MAIN_SRC     := main.c
MAIN_OBJ     := $(addprefix obj/,$(notdir $(MAIN_SRC:.c=.o)))

TEST         := bin/ringtests
TEST_SRC     := ringtests.c
TEST_OBJ     := $(addprefix obj/,$(notdir $(TEST_SRC:.c=.o)))

# Compilation configuration
################################################################################
ifeq ($(BUFFER_SIZE),)
	DEFINES := -DRING_BUFFER_MAX_LENGTH=10
else
	DEFINES := -DRING_BUFFER_MAX_LENGTH=$(BUFFER_SIZE)
endif

ifeq ($(COMPILER),)
	COMPILER := X86
endif

ifeq ($(COMPILER),X86)
  CC            := gcc
  AR            := ar rcs
endif

ifeq ($(DEBUG),)
	SPECIAL       += -O2  
else
	SPECIAL       += -O0 -g  
endif

CFLAGS       := $(DEFINES) $(SPECIAL)

# TARGETS
################################################################################

all: $(LIB) $(MAIN) $(TEST)

.PHONY: clean
clean:
	rm -rf obj
	rm -rf bin

$(LIB): $(LIB_OBJ)
	@mkdir -p bin
	$(AR) $@ $^

$(MAIN): $(MAIN_OBJ) $(LIB)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^
	@echo ringbuff Compilation done!

$(TEST): $(TEST_OBJ) $(LIB) 
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^
	@echo ringtest Compilation done!

$(LIB_OBJ): obj/%.o : %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): obj/%.o : %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): obj/%.o : %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@
	