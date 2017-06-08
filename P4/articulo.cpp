/**
 * Programación Orientada a Objetos
 * Práctica 4: Herencia y polimorfismo
 * articulo.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "articulo.hpp"

////////////////CONSTRUCTOR//////////////
Articulo::Articulo(const Autores& a, const Cadena& r, const Cadena& t,
	const Fecha& f, double p): autores_(a), codigo_referencia_(r), titulo_(t),
	fecha_publicacion_(f), precio_(p){ if(a.empty()) throw Autores_vacios();}

////////////////OPERADOR DE INSERCIÓN//////////////
std::ostream& operator <<(std::ostream& os, const Articulo& a) noexcept{
	os << "[" << a.referencia() << "] \"" << a.titulo() << "\", de";

	for (auto i = a.autores().begin(); i != a.autores().end(); ++i){
		if (i==a.autores().begin()) os << " " << (*i)->apellidos();
		else os << ", " << (*i)->apellidos();
	}

	os << ". " << a.f_publi().anno() << ". " << std::fixed << std::setprecision(2)
	   << a.precio() << " €\n\t";

	a.impresion_especifica(os);

	return os;
}

void Libro::impresion_especifica(std::ostream& os) const noexcept{
	os  << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const noexcept{
	os  << tam_ << " MB, " << stock_ << " unidades.";
}

void LibroDigital::impresion_especifica(std::ostream& os) const noexcept{
	os << "A la venta hasta el " << f_expir_ << ".";
}
