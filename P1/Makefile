# Programación Orientada a Objetos
# Práctica 1: Biblioteca de E/S
#
# Autor: Carlos Gallardo Polanco

# Cabeceras
VPATH = ../Tests-auto:.
# Compilador
CXX = clang++
# Flags del compilador y preprocesador
CXXFLAGS = -g -Wall -pedantic -std=c++11
CPPFLAGS = -I../Tests-auto -I. -DP1

# Código ejecutable
EXES = test-P1-auto test-P1-consola
# Código objeto
OBJECTS = fecha.o cadena.o test-auto.o test-P1-auto.o test-P1-consola.o test-caso0-fecha-auto.o test-caso0-cadena-auto.o

all:$(EXES)

fecha.o: fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-consola: test-P1-consola.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-auto.o: test-P1-auto.cpp fecha.hpp cadena.hpp

test-P1-consola.o: test-P1-consola.cpp fecha.hpp cadena.hpp

test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h

# Comprueba los checks con Make_check.mk
checks: ; ${MAKE} -f Make_check.mk $@
checks_clean: ; ${MAKE} -f Make_check.mk clean

# Comprueba los test
tests: ; ./test-P1-auto ; ./test-P1-consola
tests_a: ; ./test-P1-auto
tests_c: ; ./test-P1-consola

# Comprueba las fugas de memoria
valgrind:
	valgrind -q ./test-P1-auto -l minimal
	valgrind -q ./test-P1-consola

clean:
	$(RM) $(OBJECTS) $(EXES) *~
