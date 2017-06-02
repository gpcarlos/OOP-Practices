/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * articulo.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "articulo.hpp"

////////////////OPERADOR DE INSERCCIÓN//////////////
std::ostream& operator <<(std::ostream& os, const Articulo& a){
	os << "[" << a.referencia() << "] \"" << a.titulo() << "\", "
	<< a.f_publi().anno() << ". " << std::fixed << std::setprecision(2)
	<< a.precio() << "€";

	return os;
}
