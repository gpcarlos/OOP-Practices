/**
 * Programación Orientada a Objetos
 * Práctica 1: Biblioteca de E/S
 * fecha.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <ctime> // std::tm, std::time_t, strftime...
#include <clocale> // std::setlocale
#include <cstdio> // sscanf
#include <iostream>

class Fecha {
	public:
		static const int AnnoMinimo=1902, AnnoMaximo=2037;

		class Invalida{
			public:
				Invalida(const char* m): motivo_(m){}
				const char* por_que() const{ return motivo_;}
			private:
				const char* motivo_;
		};

		////////////////CONSTRUCTORES////////////////
		explicit Fecha(int=0, int=0, int=0); // Constructor de la clase
		Fecha(const char* cadena); // Constructor de conversión de cadena a caracteres

		////////////////CONVERSOR////////////////
		const char* cadena() const;

		////////////////SOBRECARGA DE OPERADORES////////////////
		Fecha& operator+=(int d);
		Fecha& operator-=(int d);
		Fecha operator+(int d) const;
		Fecha operator-(int d) const;
		Fecha& operator++();
		Fecha& operator--();
		Fecha operator++(int);
		Fecha operator--(int);

		////////////////MÉTODOS OBSERVADORES////////////////
		int dia() const noexcept{ return dia_; }
		int mes() const noexcept{ return mes_; }
		int anno() const noexcept{ return anno_; }

	private:
		int dia_, mes_, anno_;
		void fecha_valida() const;
};

////////////////SOBRECARGA DE OPERADORES////////////////
long operator-(const Fecha& f1, const Fecha& f2);
bool operator== (const Fecha& f1, const Fecha& f2);
bool operator!= (const Fecha& f1, const Fecha& f2);
bool operator< (const Fecha& f1, const Fecha& f2);
bool operator> (const Fecha& f1, const Fecha& f2);
bool operator<= (const Fecha& f1, const Fecha& f2);
bool operator>= (const Fecha& f1, const Fecha& f2);

////////////////OPERADORES DE INSERCIÓN Y EXTRACCIÓN////////////////
std::istream& operator>> (std::istream& is, Fecha& fecha);
std::ostream& operator<< (std::ostream& os, const Fecha& fecha);

#endif
