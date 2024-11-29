#------------------------------------------------------------------------------
# File:   Makefile
# Author: Flavio Tolosana Hernando (845689)   
# Date:   noviembre 2024
# Coms:   makefile para el ejercicio 4 de compresion de Algoritmia Avanzada
#------------------------------------------------------------------------------
#-----------------------------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -std=c++11      #opciones de compilación
RM = rm -f -r				#comando para borrar ficheros
OBJ_DIR = build
BIN_DIR = bin
LDFLAGS =                 #opciones de linkado
TARGET = ${BIN_DIR}/LZ78            
OBJS = 	${OBJ_DIR}/LZ78.o \
		${OBJ_DIR}/bitWriter.o \
		${OBJ_DIR}/bitReader.o

all:	${TARGET}
#-----------------------------------------------------------
${TARGET}: ${OBJS}
	mkdir -p ${BIN_DIR}
	${CC} ${OBJS} -o ${TARGET} ${CPPFLAGS}

${OBJ_DIR}/%.o: src/%.cpp
	mkdir -p ${OBJ_DIR}
	${CC} -c ${CPPFLAGS} $< -o $@

# Elimina los archivos objeto y el ejecutable
.PHONY: clean
clean: 
	${RM} ${BIN_DIR} ${OBJ_DIR}
