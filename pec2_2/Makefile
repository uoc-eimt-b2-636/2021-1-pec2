# compilador y binario a generar

CC                    := gcc
BIN                   := pec2_2

# directorios

BUILD_DIR             := ./build
BUILD_DIR_ABS         := $(abspath $(BUILD_DIR))

FREERTOS_DIR_REL      := ../freertos
FREERTOS_DIR          := $(abspath $(FREERTOS_DIR_REL))

KERNEL_DIR            := ${FREERTOS_DIR}/src

# ficheros de cabeceras

INCLUDE_DIRS          := -I.
INCLUDE_DIRS          += -I${FREERTOS_DIR}/inc
INCLUDE_DIRS          += -I${FREERTOS_DIR}/portable/Posix
INCLUDE_DIRS          += -I${FREERTOS_DIR}/portable/Posix/utils

# ficheros fuente

SOURCE_FILES          := $(wildcard *.c)

SOURCE_FILES          += $(wildcard ${KERNEL_DIR}/*.c)

SOURCE_FILES          += ${FREERTOS_DIR}/portable/MemMang/heap_3.c
SOURCE_FILES          += ${FREERTOS_DIR}/portable/Posix/utils/wait_for_event.c
SOURCE_FILES          += ${FREERTOS_DIR}/portable/Posix/port.c

# parametros compilador y linkador

CFLAGS                :=   -ggdb3
LDFLAGS               :=   -ggdb3 -pthread -lm

CPPFLAGS              :=   $(INCLUDE_DIRS)
CPPFLAGS              +=   -DprojCOVERAGE_TEST=1

CFLAGS                +=   -O3
LDFLAGS               +=   -O3

# ficheros objeto

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

# objetivos, dependencias y reglas

${BIN} : $(BUILD_DIR)/$(BIN)

${BUILD_DIR}/${BIN} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ ${LDFLAGS} -o $@

${BUILD_DIR}/%.o : %.c Makefile
	-mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	-rm -rf $(BUILD_DIR) output.txt
