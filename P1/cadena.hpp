/**
 * Programación Orientada a Objetos
 * Práctica 1: Biblioteca de E/S
 * cadena.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring> // size_t, strcpy, strlen...
#include <stdexcept> // std::out_of_range
#include <iostream>
#include <iterator>
// Para P2
#include <functional>
#include <string>

class Cadena{
	public:
		static const size_t npos = static_cast<size_t>(-1);

		////////////////CONSTRUCTORES//////////////
		explicit Cadena (size_t tam=0, char caracter=' ');
		Cadena (const Cadena& cadena);
		Cadena (const char* cadena);
		Cadena (const char* cadena, size_t n);
		Cadena (const Cadena& cadena, size_t inicio, size_t longitud=npos);

		////////////////MÉTODO OBSERVADOR////////////////
		size_t length() const noexcept{ return tam_;}

		////////////////CONVERSOR////////////////
		const char* c_str() const noexcept{return s_;}

		////////////////SOBRECARGA DE OPERADORES////////////////
		Cadena& operator= (const char* cadena);
		Cadena& operator= (const Cadena& cadena);
		Cadena& operator+= (const Cadena& cadena);
		char operator[] (size_t posicion) const noexcept;
		char& operator[] (size_t posicion) noexcept;

		////////////////FUNCIONES AT////////////////
		char at (size_t posicion) const;
		char& at (size_t posicion);

		////////////////DESTRUCTOR////////////////
		~Cadena();

		////////////////SUBSTR////////////////
		Cadena substr(size_t inicio, int longitud) const;

		////////////////MOVIMIENTO////////////////
		Cadena(Cadena&& cadena);
		Cadena& operator= (Cadena&& cadena);

		////////////////ITERADORES////////////////
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator begin() noexcept{ return s_;}
		const_iterator begin() const noexcept{ return s_;}
		const_iterator cbegin() const noexcept{ return s_;}

		iterator end() noexcept{ return s_+tam_;}
		const_iterator end() const noexcept{ return s_+tam_;}
		const_iterator cend() const noexcept{ return s_+tam_;}

		reverse_iterator rbegin() noexcept{ return reverse_iterator(end());}
		const_reverse_iterator rbegin() const noexcept{ return const_reverse_iterator(end());}
		const_reverse_iterator crbegin() const noexcept{ return const_reverse_iterator(end());}

		reverse_iterator rend() noexcept{ return reverse_iterator(begin());}
		const_reverse_iterator rend() const noexcept{ return const_reverse_iterator(begin());}
		const_reverse_iterator crend() const noexcept{ return const_reverse_iterator(begin());}

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

////////////////OPERADORES DE INSERCIÓN Y EXTRACCIÓN////////////////
std::istream& operator>> (std::istream& is, Cadena& cadena);
std::ostream& operator<< (std::ostream& os, const Cadena& cadena);

// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std {
template <> struct hash<Cadena> {
	size_t operator()(const Cadena& cad) const
		{ // conversión const char* ->string
			return hash<string>{}(cad.c_str());
		}
	};
}

#endif
