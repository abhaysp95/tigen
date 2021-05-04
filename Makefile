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
DIRS            = ${BIN_DIR} ${OBJ_DIR} ${DEBUG_DIR}


SRC           =  $(wildcard ${SRC_DIR}/*.cpp)
SRC           := ${SRC} $(wildcard ${SRC_EXT_DIR}/*.cpp)
OBJ           =  $(addprefix ${OBJ_DIR}/, $(notdir ${SRC:.cpp=.o}) $(notdir ${SRC_EXT:.cpp=.o}))
BIN           =  ${BIN_DIR}/$(notdir $(realpath .))
DEBUG_OBJ     =  $(addprefix ${DEBUG_DIR}/, $(notdir ${SRC:.cpp=.o}) $(notdir ${SRC_EXT:.cpp=.o}))
DEBUG_BIN     =  $(addprefix ${DEBUG_DIR}/, $(notdir $(realpath .)))


all: dir ${BIN}

dir:
	mkdir -p ${DIRS}


${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CFLAG} -I ${INC_DIR} -c -o $@ $^

${OBJ_DIR}/%.o: ${SRC_EXT_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CFLAG} -I ${INC_EXT_DIR} -c -o $@ $^

${BIN}: ${OBJ}
	-@echo "Linking $? -> $@"
	${LD} ${LFLAG} -o $@ ${OBJ_DIR}/*.o
	-@echo "copied ${BIN} -> $(notdir $(realpath .))"
	cp -f ${BIN} .


debug: dir ${DEBUG_BIN}

${DEBUG_DIR}/%.o: ${SRC_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CDFLAG} -I ${INC_DIR} -c -o $@ $^

${DEBUG_DIR}/%.o: ${SRC_EXT_DIR}/%.cpp
	-@echo "compiling $? -> $@"
	${CC} ${CDFLAG} -I ${INC_EXT_DIR} -c -o $@ $^

${DEBUG_BIN}: ${DEBUG_OBJ}
	-@echo "Linking to -> $@"
	${LD} ${LDFLAG} -o $@ ${DEBUG_DIR}/*.o


clean:
	rm -rf ${DIRS} $(notdir $(realpath .))

help:
	-@echo "src: ${SRC}"
	-@echo "src_dir: ${SRC_DIR}"
	-@echo "src_ext: ${SRC_EXT}"
	-@echo "src_ext_dir: ${SRC_EXT_DIR}"
	-@echo "obj: ${OBJ}"
	-@echo "obj_dir: ${OBJ_DIR}"
	-@echo "dir: ${DIRS}"
	-@echo "bin: ${BIN}"

.SILENT:
.PHONY: all dir debug clean