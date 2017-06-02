/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * articulo.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <iomanip>

class Articulo{
	public:
		////////////////CONSTRUCTOR//////////////
		Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p,
			unsigned s): codigo_referencia_(r), titulo_(t), fecha_publicacion_(f),
			precio_(p), stock_(s){}

		////////////////OBSERVADORES//////////////
		const Cadena& referencia() const noexcept{ return codigo_referencia_;}
		const Cadena& titulo() const noexcept{ return titulo_;}
		const Fecha& f_publi() const noexcept{ return fecha_publicacion_;}
		double precio() const noexcept{ return precio_;}
		double& precio() noexcept{ return precio_;}
		unsigned stock() const noexcept{ return stock_;}
		unsigned& stock() noexcept{ return stock_;}

	private:
		Cadena codigo_referencia_;
		Cadena titulo_;
		Fecha fecha_publicacion_;
		double precio_;
		unsigned stock_;
};

////////////////OPERADOR DE INSERCCIÓN//////////////
std::ostream& operator <<(std::ostream& os, const Articulo& a);

#endif
