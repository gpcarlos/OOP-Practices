/**
 * Programación Orientada a Objetos
 * Práctica 2: Relaciones de asociación y contenedores de la STL
 * articulo.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "articulo.hpp"

////////////////OPERADOR DE INSERCIÓN//////////////
std::ostream& operator <<(std::ostream& os, const Articulo& a){
	os << "[" << a.referencia() << "] \"" << a.titulo() << "\", "
	<< a.f_publi().anno() << ". " << std::fixed << std::setprecision(2)
	<< a.precio() << "€";

	return os;
}
