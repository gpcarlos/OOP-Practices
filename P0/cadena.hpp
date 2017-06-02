/**
 * Programación Orientada a Objetos
 * Práctica 0: Clases, objetos y excepciones
 * cadena.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring> // size_t, strcpy, strlen...
#include <stdexcept> // std::out_of_range

class Cadena{
	public:
		static const size_t npos = -1;

		////////////////CONSTRUCTORES//////////////
		explicit Cadena (size_t tam=0, char caracter=' ');
		Cadena (const Cadena& cadena);
		Cadena (const char* cadena);
		Cadena (const char* cadena, size_t n);
		Cadena (const Cadena& cadena, size_t inicio, size_t longitud=npos);

		////////////////MÉTODO OBSERVADOR////////////////
		size_t length() const noexcept{ return tam_;}

		////////////////SOBRECARGA DE OPERADORES////////////////
		operator const char* () const;
		Cadena& operator= (const char* cadena);
		Cadena& operator= (const Cadena& cadena);
		Cadena& operator+= (const Cadena& cadena);
		char operator[] (size_t posicion) const;
		char& operator[] (size_t posicion);

		////////////////FUNCIONES AT////////////////
		char at (size_t posicion) const;
		char& at (size_t posicion);

		////////////////DESTRUCTOR////////////////
		~Cadena();

		////////////////SUBSTR////////////////
		Cadena substr(size_t inicio, int longitud) const;
	private:
		char* s_;
		size_t tam_;
};

////////////////SOBRECARGA DE OPERADORES////////////////
Cadena operator+ (const Cadena& cadena1, const Cadena& cadena2) noexcept;
bool operator == (const Cadena& cadena1, const Cadena& cadena2) noexcept;
bool operator != (const Cadena& cadena1, const Cadena& cadena2) noexcept;
bool operator < (const Cadena& cadena1, const Cadena& cadena2) noexcept;
bool operator > (const Cadena& cadena1, const Cadena& cadena2) noexcept;
bool operator <= (const Cadena& cadena1, const Cadena& cadena2) noexcept;
bool operator >= (const Cadena& cadena1, const Cadena& cadena2) noexcept;

#endif
