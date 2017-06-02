# Programación Orientada a Objetos
# Práctica 0: Clases, objetos y excepciones
# 
# Autor: Carlos Gallardo Polanco

# Cabeceras
VPATH = ../Tests-auto:.
# Compilador
CXX = clang++ 
# Flags del compilador y preprocesador
CXXFLAGS = -g -Wall -pedantic -std=c++11 
#-fmax-errors=10
CPPFLAGS = -I../Tests-auto -I. -DP0

# Código ejecutable
EXES = test-P0-auto test-P0-consola
# Código objeto
OBJECTS = fecha.o cadena.o test-P0-auto.o test-P0-consola.o 

all:$(EXES)

fecha.o: fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P0-auto.o: test-P0-auto.cpp fecha.hpp cadena.hpp

test-P0-consola.o: test-P0-consola.cpp fecha.hpp cadena.hpp

test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h

checks: ; ${MAKE} -f Make_check.mk $@

clean:
	$(RM) $(OBJECTS) $(EXES) *~