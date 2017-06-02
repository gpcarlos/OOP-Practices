/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * tarjeta.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "tarjeta.hpp"

/************************NUMERO************************/

bool luhn(const Cadena& numero);

////////////////CONTRUCTOR////////////////
Numero::Numero(const Cadena& num): numero_(num){
	char* nm = new char[num.length() +1];

	size_t j = 0;
	for(size_t i =0 ; i<num.length(); ++i){
		if(!isspace(num[i])){
			if(!isdigit(num[i])) throw Incorrecto(DIGITOS);
			nm[j++] = num[i];
		}
	}
	nm[j]=0;
	if(numero_ != nm) numero_ = nm;
	delete[] nm;

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
	os << enumerado[i] << std::endl;

	return os;
}

std::ostream& operator << (std::ostream& os, const Tarjeta& t){
	os << t.tipo() << t.numero() << std::endl<< t.titular_facial() << std::endl
	<< "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes()
	<< "/" << std::setw(2) << t.caducidad().anno() % 100 << std::endl;

	return os;
}
