/**
 * Programación Orientada a Objetos
 * Práctica 1: Biblioteca de E/S
 * cadena.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "cadena.hpp"

////////////////CONSTRUCTORES//////////////
Cadena::Cadena (size_t tam, char caracter): s_(new char[tam+1]), tam_(tam){
	memset(s_,caracter,tam_);
	s_[tam_]='\0';
}

Cadena::Cadena (const Cadena& cadena): s_(new char[cadena.tam_+1]),
	tam_(cadena.tam_){
	strcpy(s_, cadena.s_);
}

Cadena::Cadena (const char* cadena): s_(new char[strlen(cadena)+1]),
	tam_(strlen(cadena)){
	strcpy(s_,cadena);
	s_[tam_]='\0';
}

Cadena::Cadena (const char* cadena, size_t n){
	if(n>strlen(cadena)){
		s_= new char[strlen(cadena)+1];
		tam_ = strlen(cadena);
	}else{
		s_ = new char[n+1];
		tam_ = n;
	}
	memcpy(s_,cadena,tam_);
	s_[tam_]='\0';
}

Cadena::Cadena (const Cadena& cadena, size_t inicio, size_t longitud){
	if(inicio>=cadena.tam_) throw std::out_of_range("Error. Fuera de rango.");
	if(inicio+longitud>cadena.tam_ || longitud==npos){
		s_ = new char[cadena.tam_-inicio+1];
		tam_ = cadena.tam_-inicio;
	}else{
		s_ = new char[longitud+1];
		tam_ = longitud;
	}
	memcpy(s_,cadena.c_str()+inicio,tam_);
	s_[tam_]='\0';
}

////////////////SOBRECARGA DE OPERADORES////////////////
Cadena& Cadena::operator= (const char* cadena){
	delete[] s_;
	s_ = new char[(tam_ = strlen(cadena))+1];
	strcpy(s_, cadena);
	return *this;
}

Cadena& Cadena::operator= (const Cadena& cadena){
	if(this != &cadena){
		delete[] s_;
		s_ = new char[cadena.tam_+1];
		tam_ = cadena.tam_;
		strcpy(s_,cadena.c_str());
	}
	return *this;
}

Cadena& Cadena::operator+= (const Cadena& cadena){ // Concatenación
	char* conc = new char[tam_+cadena.tam_ + 1];
	strcpy(conc, s_);
	strcat(conc, cadena.s_);
	*this = conc;
	delete[] conc;
	return *this;
}

Cadena operator+ (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	Cadena concatenada(cadena1);
	concatenada+=cadena2;
	return concatenada;
}

bool operator == (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	return strcmp(cadena1.c_str(), cadena2.c_str())==0;
}

bool operator != (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	return strcmp(cadena1.c_str(), cadena2.c_str())!=0;
}

bool operator < (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	return strcmp(cadena1.c_str(), cadena2.c_str())<0;
}

bool operator > (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	return strcmp(cadena1.c_str(), cadena2.c_str())>0;
}

bool operator <= (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	return strcmp(cadena1.c_str(), cadena2.c_str())<=0;
}

bool operator >= (const Cadena& cadena1, const Cadena& cadena2) noexcept{
	return strcmp(cadena1.c_str(), cadena2.c_str())>=0;
}

char Cadena::operator[] (size_t posicion) const noexcept{
	return s_[posicion];
}

char& Cadena::operator[] (size_t posicion) noexcept{
	return s_[posicion];
}

////////////////FUNCIONES AT////////////////
char Cadena::at (size_t posicion) const{
	if(posicion>=tam_) throw std::out_of_range("Error. Fuera de rango.");
	return s_[posicion];
}

char& Cadena::at (size_t posicion){
	if(posicion>=tam_) throw std::out_of_range("Error. Fuera de rango.");
	return s_[posicion];
}

////////////////DESTRUCTOR////////////////
Cadena::~Cadena(){ delete[] s_;}

////////////////SUBSTR////////////////
Cadena Cadena::substr (size_t inicio, int longitud) const{
	if(longitud<0 || inicio>=tam_ || inicio+longitud>=tam_)
		throw std::out_of_range("Error. Fuera de rango.");
	Cadena recortada(longitud);
	memcpy(recortada.s_,s_+inicio,recortada.tam_);
	recortada.s_[longitud]='\0';
	return recortada;
}

///////////////////OPERADORES DE INSERCIÓN Y EXTRACCIÓN////////////////
std::istream& operator>> (std::istream& is, Cadena& cadena){
	char ext[32]="";
	is >> ext;
	cadena = Cadena(ext);
	return is;
}

std::ostream& operator<< (std::ostream& os, const Cadena& cadena){
	os << cadena.c_str();
	return os;
}

////////////////MOVIMIENTO////////////////
Cadena::Cadena (Cadena&& cadena): s_(cadena.s_), tam_(cadena.tam_){
	cadena.s_=nullptr;
	cadena.tam_=0;
}

Cadena& Cadena::operator= (Cadena&& cadena){
	if(this != &cadena){
		delete[] s_;
		s_=cadena.s_;
		tam_=cadena.tam_;
		cadena.s_=nullptr;
		cadena.tam_=0;
	}
	return *this;
}
