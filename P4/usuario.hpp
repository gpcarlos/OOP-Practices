/**
 * Programación Orientada a Objetos
 * Práctica 4: Herencia y polimorfismo
 * usuario.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "cadena.hpp"
#include "articulo.hpp"

extern "C"{
	#include <unistd.h> // crypt
}
#include <random>
#include <map>
#include <unordered_map>
#include <unordered_set>

class Tarjeta;

class Clave{
	public:
		enum Razon {CORTA, ERROR_CRYPT};

		class Incorrecta{
			public:
				Incorrecta(Razon r): razon_(r){}
				Razon razon() const{ return razon_;}
			private:
				Razon razon_;
		};

		////////////////CONSTRUCTOR////////////////
		Clave(const char* clave_en_claro);

		////////////////OBSERVADOR////////////////
		const Cadena& clave() const noexcept{ return clave_cifrada_;}

		////////////////VERIFICA////////////////
		bool verifica (const char* c) const;
	private:
		Cadena clave_cifrada_;
};

class Tarjeta;
class Numero;

class Usuario{
	public:
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;
		typedef	std::unordered_set<Cadena> Identificadores;

		class Id_duplicado{
			public:
				Id_duplicado(const Cadena& i): ident_(i){}
				const Cadena& idd() const{ return ident_;}
			private:
				Cadena ident_;
		};

		////////////////CONSTRUCTOR////////////////
		Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const Cadena& d,
			const Clave& c);

		////////////////COPIA ELIMINADA///////////////
		Usuario(const Usuario& u) = delete;
		Usuario& operator= (const Usuario& u) = delete;

		////////////////OBSERVADORES////////////////
		const Cadena& id() const noexcept{ return indentificador_;}
		const Cadena& nombre() const noexcept{ return nombre_;}
		const Cadena& apellidos() const noexcept{ return apellidos_;}
		const Cadena& direccion() const noexcept{ return direccion_;}
		const Tarjetas& tarjetas() const noexcept{ return tarjetas_;}
		const Articulos& compra() const noexcept{ return carrito_;}
		size_t n_articulos() const noexcept{ return carrito_.size();}

		////////////////ASOCIACIÓN CON TARJETA////////////////
		void es_titular_de(const Tarjeta& t);
		void no_es_titular_de(const Tarjeta& t);

		////////////////ASOCIACIÓN CON ARTICULO////////////////
		void compra (const Articulo& art, unsigned cant=1);

		////////////////OPERADOR DE INSERCIÓN////////////////
		friend std::ostream& operator << (std::ostream& os, const Usuario& u);

		////////////////DESTRUCTOR////////////////
		~Usuario();

	private:
		Cadena indentificador_;
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
		Clave clave_;
		Tarjetas tarjetas_;
		Articulos carrito_;
		static Identificadores idents_;
};

////////////////MOSTRAT CARRO////////////////
std::ostream& mostrar_carro(std::ostream& os, const Usuario& u);

#endif

////////////////
