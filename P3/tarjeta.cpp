/**
 * Programación Orientada a Objetos
 * Práctica 2: Relaciones de asociación y contenedores de la STL
 * tarjeta.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "tarjeta.hpp"
#include "usuario.hpp"

/************************NUMERO************************/

bool luhn(const Cadena& numero);

struct EsDigito{
	bool operator()(char c) const{ return std::isdigit(c);}
};

////////////////CONTRUCTOR////////////////
Numero::Numero(const Cadena& num):numero_(num){
	Cadena::iterator fin = std::remove_if(
		numero_.begin(), numero_.end(), [](char c){ return std::isspace(c); } );

	if(fin!= numero_.end()){
		*fin='\0';
		Cadena sd(numero_.c_str());
		numero_=sd;
	}
	if ( std::find_if(numero_.begin(), numero_.end(),
	std::not1(std::function<bool(char)>(EsDigito())) )!= numero_.end() ){
    throw Incorrecto(DIGITOS);
  }

	size_t j=numero_.length();
	if(j<13 or j>19) throw Incorrecto(LONGITUD);
	if(not luhn(numero_)) throw Incorrecto(NO_VALIDO);

}

////////////////OPERADOR DE CONVERSIÓN////////////////
Numero::operator const char*() const noexcept{
	return numero_.c_str();
}

////////////////OPERADOR MENOR////////////////
bool operator< (const Numero& n1, const Numero& n2){
	return strcmp(n1,n2)<0;
}

/************************TARJETA************************/

////////////////CONSTRUCTOR////////////////
Tarjeta::Tarjeta(Tipo t, const Numero& n, Usuario& u, const Fecha& f)
	:tipo_(t), num_(n), titular_(&u), caducidad_(f),
	titular_facial_(u.nombre()+" "+u.apellidos()){
	if(f<Fecha()) throw Caducada(f);
	u.es_titular_de(*this);
}

////////////////ANULAR TITULAR////////////////
void Tarjeta::anular_titular(){
	titular_=nullptr;
}

////////////////DESTRUCTOR////////////////
Tarjeta::~Tarjeta(){
	if(titular_){
		Usuario* u = const_cast<Usuario*>(titular_);
		u->no_es_titular_de(*this);
	}
}

////////////////OPERADOR MENOR////////////////
bool operator < (const Tarjeta& t1, const Tarjeta& t2){
	return t1.numero()<t2.numero();
}

////////////////OPERADORES DE INSERCIÓN////////////////
std::ostream& operator << (std::ostream& os, const Tarjeta::Tipo& t){
	const char* enumerado[] = {"VISA", "Mastercard", "Maestro", "JCB",
		"AmericanExpress"};
	int i = static_cast<int>(t);
	os << enumerado[i];

	return os;
}

std::ostream& operator << (std::ostream& os, const Tarjeta& t){
	os << t.tipo() << t.numero() << std::endl<< t.titular_facial() << std::endl
	<< "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes()
	<< "/" << std::setw(2) << t.caducidad().anno() % 100 << std::endl;

	return os;
}
