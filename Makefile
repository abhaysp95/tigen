# /* --- Makefile --- */

CC     = g++
CFLAG  = -Wall -std=c++14
CDFLAG = -Wall -std=c++14 -g
LD     = g++
LDFLAG = -v
LFLAG  =


SRC_DIR         = src
SRC_EXT_DIR     = src/extras
OBJ_DIR         = obj
OBJ_EXT_DIR     = obj/extras
INC_DIR         = inc
INC_EXT_DIR     = inc/extras
BIN_DIR         = bin
DEBUG_DIR       = debug
DEBUG_EXT_DIR   = debug/extras
DIRS            = ${BIN_DIR} ${OBJ_DIR} ${OBJ_EXT_DIR} ${DEBUG_DIR} ${DEBUG_EXT_DIR}


SRC           = $(wildcard ${SRC_DIR}/*.cpp)
SRC_EXT       = $(wildcard ${SRC_EXT_DIR}/*.cpp)
OBJ           = $(addprefix ${OBJ_DIR}/, $(notdir ${SRC:.cpp=.o}))
OBJ_EXT       = $(addprefix ${OBJ_EXT_DIR}/, $(notdir ${SRC_EXT:.cpp=.o}))
BIN           = ${BIN_DIR}/$(notdir $(realpath .))
DEBUG_OBJ     = $(addprefix ${DEBUG_DIR}/, $(notdir ${SRC:.cpp=.o}))
DEBUG_EXT_OBJ = $(addprefix ${DEBUG_EXT_DIR}/, $(notdir ${SRC_EXT:.cpp=.o}))
DEBUG_BIN     = $(addprefix ${DEBUG_DIR}/, $(notdir $(realpath .)))


all: dir ${BIN}

dir:
	mkdir -p ${DIRS}


${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CFLAG} -I ${INC_DIR} -c -o $@ $^

${OBJ_EXT_DIR}/%.o: ${SRC_EXT_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CFLAG} -I ${INC_EXT_DIR} -c -o $@ $^

${BIN}: ${OBJ_EXT} ${OBJ}
	-@echo "Linking $? -> $@"
	${LD} ${LFLAG} -o $@ ${OBJ_DIR}/*.o
	-@echo "copied ${BIN} -> $(notdir $(realpath .))"
	cp -f ${BIN} .


debug: dir ${DEBUG_BIN}

${DEBUG_DIR}/%.o: ${SRC_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CDFLAG} -I ${INC_DIR} -c -o $@ $^

${DEBUG_EXT_DIR}/%.o: ${SRC_EXT_DIR}%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CDFLAG} -I ${INC_EXT_DIR} -c -o $@ $^

${DEBUG_BIN}: ${DEBUG_EXT_OBJ} ${DEBUG_OBJ}
	-@echo "Linking to -> $@"
	${LD} ${LDFLAG} -o $@ ${DEBUG_DIR}/*.o


clean:
	rm -rf ${DIRS} $(notdir $(realpath .))

.SILENT:
.PHONY: all dir debug clean