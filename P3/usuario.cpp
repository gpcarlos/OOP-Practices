/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * usuario.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "usuario.hpp"
#include "tarjeta.hpp"

Usuario::Identificadores Usuario::idents_;

/************************CLAVE************************/

////////////////CONTRUCTOR////////////////
Clave::Clave(const char* clave_en_claro){
	if(strlen(clave_en_claro)<5) throw Incorrecta(CORTA);

	static const char* const cv =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuwxyz0123456789./";
	static std::size_t longcv = sizeof(cv)-1;
	static std::random_device r;
	static std::uniform_int_distribution<std::size_t> dist(0, longcv-1);

	char sal[] = {cv[dist(r)], cv[dist(r)]};

	if(char* contasena = crypt(clave_en_claro, sal))
		clave_cifrada_=contasena;
	else throw Incorrecta(ERROR_CRYPT);
}

////////////////VERIFICA////////////////
bool Clave::verifica(const char* clave_en_claro) const{
	char* tc = crypt(clave_en_claro, clave_cifrada_.c_str());
	return strcmp(tc,clave_cifrada_.c_str())==0;
}

/************************USUARIO************************/

////////////////CONSTRUTOR////////////////
Usuario::Usuario(const Cadena& i, const Cadena& n, const Cadena& a,
	const Cadena& d, const Clave& c): indentificador_(i), nombre_(n),
	apellidos_(a), direccion_(d), clave_(c){

	if(!idents_.insert(i).second) throw Id_duplicado(i);
}


////////////////ASOCIACIÓN CON TARJETA////////////////
void Usuario::es_titular_de(const Tarjeta& t){
	if(t.titular()==this){
		tarjetas_[t.numero()]=const_cast<Tarjeta*>(&t);
		// Es necesario const_cast para quitarle el const a t
	}
}

void Usuario::no_es_titular_de(const Tarjeta& t){
	tarjetas_.erase(t.numero());
}

////////////////ASOCIACIÓN CON ARTICULO////////////////
void Usuario::compra (const Articulo& art, unsigned cant){
	if(!cant) carrito_.erase(const_cast<Articulo*>(&art));
	else carrito_[const_cast<Articulo*>(&art)] = cant;
}

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator << (std::ostream& os, const Usuario& u){
	os << u.indentificador_ << " [" << u.clave_.clave() << "] "
	<< u.nombre_ << " " << u.apellidos_ << std::endl
	<< u.direccion_ << std::endl << "Tarjetas:" << std::endl;
	for (auto i : u.tarjetas_) os << *i.second << std::endl;

	return os;
}

////////////////DESTRUCTOR////////////////
Usuario::~Usuario(){
	for(auto& i : tarjetas_)
		i.second->anular_titular();
	idents_.erase(indentificador_);
}

////////////////MOSTRAR CARRO////////////////
std::ostream& mostrar_carro(std::ostream& os, const Usuario& u){
	os << "Carrito de compra de " << u.id() << " [Artículos: "
 	<< u.n_articulos() << "]" << std::endl << " Cant. Artículo" << std::endl
	<< "===============================================" << std::endl;
	for(auto i : u.compra()){
		os << "  " << i.second << "    [" << i.first->referencia() << "] \""
		<< i.first->titulo() << "\", " << i.first->f_publi().anno() << ". "
		<< std::fixed << std::setprecision(2) << i.first->precio()	<< " €"
		<< std::endl;
	}

	return os;
}
