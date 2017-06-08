/**
 * Programación Orientada a Objetos
 * Práctica 4: Herencia y polimorfismo
 * articulo.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"
#include <iomanip>
#include <set>

class Autor{
	public:
		////////////////CONSTRUCTOR//////////////
		Autor(const Cadena& n, const Cadena& a, const Cadena& d) noexcept:
			nombre_(n), apellidos_(a), direccion_(d){}

		////////////////OBSERVADORES//////////////
		const Cadena& nombre() const noexcept{ return nombre_;}
		const Cadena& apellidos() const noexcept{ return apellidos_;}
		const Cadena& direccion() const noexcept{ return direccion_;}
	private:
		Cadena nombre_, apellidos_, direccion_;
};

class Articulo{
	public:
		class Autores_vacios{};

		typedef std::set<Autor*> Autores;

		////////////////CONSTRUCTOR//////////////
		Articulo(const Autores& a, const Cadena& r, const Cadena& t,
			const Fecha& f, double p);

		////////////////OBSERVADORES//////////////
		const Autores& autores() const noexcept{ return autores_;}
		const Cadena& referencia() const noexcept{ return codigo_referencia_;}
		const Cadena& titulo() const noexcept{ return titulo_;}
		const Fecha& f_publi() const noexcept{ return fecha_publicacion_;}
		double precio() const noexcept{ return precio_;}
		double& precio() noexcept{ return precio_;}

		////////////////IMPRESIÓN ESPECÍFICA////////////// Método virtual puro
		virtual void impresion_especifica(std::ostream& os) const noexcept = 0;

		///////////////DESTRUCTOR//////////////
		virtual ~Articulo(){}

	private:
		Autores autores_;
		Cadena codigo_referencia_;
		Cadena titulo_;
		Fecha fecha_publicacion_;
		double precio_;
};

////////////////OPERADOR DE INSERCIÓN//////////////
std::ostream& operator <<(std::ostream& os, const Articulo& a) noexcept;


class ArticuloAlmacenable: public Articulo{
	public:
		////////////////CONSTRUCTOR//////////////
		ArticuloAlmacenable(const Autores& a, const Cadena& r, const Cadena& t,
			const Fecha& f, double p, unsigned s=0): Articulo(a,r,t,f,p){}

		////////////////OBSERVADOR//////////////
		unsigned stock() const noexcept{ return stock_;}
		unsigned& stock() noexcept{ return stock_;}

		//virtual ~ArticuloAlmacenable();
	private:
		unsigned stock_;
};


class Libro: public ArticuloAlmacenable{
	public:
		////////////////CONSTRUCTOR//////////////
		Libro(const Autores& a, const Cadena& r, const Cadena& t,
			const Fecha& f, double p, unsigned pag, unsigned s=0):
			ArticuloAlmacenable(a,r,t,f,p,s), paginas_(pag){}

		////////////////OBSERVADORES//////////////
		unsigned n_pag() const noexcept{ return paginas_;}

		////////////////IMPRESIÓN ESPECÍFICA//////////////
		inline void impresion_especifica(std::ostream& os) const noexcept;
	private:
		 unsigned paginas_;
};

inline void Libro::impresion_especifica(std::ostream& os) const noexcept
{ os << "\t" << paginas_ << " págs., " << stock() << " unidades.";}


class Cederron: public ArticuloAlmacenable{
	public:
		////////////////CONSTRUCTOR//////////////
		Cederron(const Autores& a, const Cadena& r, const Cadena& t,
			const Fecha& f, double p, unsigned tam, unsigned s=0):
			ArticuloAlmacenable(a,r,t,f,p,s), tamanno_(tam){}

		////////////////OBSERVADORES//////////////
		unsigned tam() const noexcept{ return tamanno_;}

		////////////////IMPRESIÓN ESPECÍFICA//////////////
		inline void impresion_especifica(std::ostream& os) const noexcept;
	private:
		 unsigned tamanno_;
};

inline void Cederron::impresion_especifica(std::ostream& os) const noexcept
{ os << "\t" << tamanno_ << " MB, " << stock() << " unidades.";}


class LibroDigital: public Articulo{
	public:
		////////////////CONSTRUCTOR//////////////
		LibroDigital(const Autores& a, const Cadena& r, const Cadena& t,
			const Fecha& f, double p, const Fecha& exp):
			Articulo(a,r,t,f,p), fecha_exp_(exp){}

		////////////////OBSERVADORES//////////////
		const Fecha& f_expir() const noexcept{ return fecha_exp_;}

		////////////////IMPRESIÓN ESPECÍFICA//////////////
		inline void impresion_especifica(std::ostream& os) const noexcept;
	private:
		 Fecha fecha_exp_;
};

inline void LibroDigital::impresion_especifica(std::ostream& os) const noexcept
{ os << "\tA la venta hasta el " << fecha_exp_ << ".";}

#endif
