/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * tarjeta.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "fecha.hpp"
#include "cadena.hpp"
#include <iomanip>
#include <algorithm>

class Usuario;

class Numero{
	public:
		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};

		class Incorrecto{
			public:
				Incorrecto(Razon r): razon_(r){}
				Razon razon() const{ return razon_;}
			private:
				Razon razon_;
		};

		////////////////CONSTRUCTOR////////////////
		Numero(const Cadena& num);

		////////////////OPERADOR DE CONVERSIÓN////////////////
		operator const char*() const noexcept;

	private:
		Cadena numero_;
};

////////////////OPERADOR MENOR////////////////
bool operator< (const Numero& n1, const Numero& n2);

class Usuario;

class Tarjeta{
	public:
		enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};

		class Caducada{
			public:
				Caducada(const Fecha& f): fecha_(f){}
				const Fecha& cuando() const{ return fecha_;}
			private:
				Fecha fecha_;
		};

		////////////////CONSTRUCTOR////////////////
		Tarjeta(Tipo t, const Numero& n, Usuario& u, const Fecha& f);

		////////////////COPIA ELIMINADA///////////////
		Tarjeta(const Tarjeta& t)=delete;
		Tarjeta& operator= (const Tarjeta& t)=delete;

		////////////////OBSERVADORES////////////////
		Tipo tipo() const{ return tipo_;}
		const Usuario* const titular() const{ return titular_;}
		const Fecha& caducidad() const{ return caducidad_;}
		const Cadena& titular_facial() const{ return titular_facial_;}
		const Numero& numero() const {return num_;}

		////////////////ANULAR TITULAR////////////////
		void anular_titular();

		////////////////DESTRUCTOR////////////////
		~Tarjeta();

	private:
		Tipo tipo_;
		Numero num_;
		const Usuario * titular_;
		Fecha caducidad_;
		Cadena titular_facial_;
};

////////////////OPERADOR MENOR////////////////
bool operator < (const Tarjeta& t1, const Tarjeta& t2);

////////////////OPERADORES DE INSERCIÓN////////////////
std::ostream& operator << (std::ostream& os, const Tarjeta::Tipo& t);
std::ostream& operator << (std::ostream& os, const Tarjeta& t);

#endif
