/**
 * Programación Orientada a Objetos
 * Práctica 0: Clases, objetos y excepciones
 * fecha.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "fecha.hpp"

////////////////CONSTRUCTORES////////////////
Fecha::Fecha (int d, int m, int a): dia_(d), mes_(m), anno_(a){
	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	if(anno_==0){ anno_=tiempo_descompuesto->tm_year + 1900; }
	if(mes_==0){ mes_=tiempo_descompuesto->tm_mon + 1; }
	if(dia_==0){ dia_=tiempo_descompuesto->tm_mday; }

	fecha_valida();
}

Fecha::Fecha (const char* cadena){
	if(sscanf(cadena, "%d/%d/%d", &dia_, &mes_, &anno_)!=3){
		throw Invalida("Cadena inválida");
	}

	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	if(anno_==0){ anno_=tiempo_descompuesto->tm_year + 1900; }
	if(mes_==0){ mes_=tiempo_descompuesto->tm_mon + 1; }
	if(dia_==0){ dia_=tiempo_descompuesto->tm_mday; }

	fecha_valida();
}

////////////////SOBRECARGA DE OPERADORES////////////////
Fecha::operator const char* () const{
	std::setlocale(LC_ALL,"es_ES.UTF8");

	std::tm fecha_actual = {};
	fecha_actual.tm_year=anno_-1900;
	fecha_actual.tm_mon=mes_-1;
	fecha_actual.tm_mday=dia_;
	std::mktime(&fecha_actual);

	static char cadena[40];
	std::strftime(cadena,40,"%A %d de %B de %Y", &fecha_actual);
	return cadena;
}

Fecha& Fecha::operator += (int d){
	if (d==0){return *this;}

	// Primero sacamos el tiempo transcurrido desde
	std::tm tiempo_desde_1900 = {};
	// el 1 de enero de 1900 hasta nuestra fecha actual
	tiempo_desde_1900.tm_year=anno_-1900;
	tiempo_desde_1900.tm_mon=mes_-1;
	tiempo_desde_1900.tm_mday=dia_;

	// Ahora pasamos nuestra fecha a segundos
	std::time_t fecha_en_segundos = std::mktime(&tiempo_desde_1900);
	// y le sumamos los días en segundos
	fecha_en_segundos = fecha_en_segundos + d*86400;

	// Por último, pasamos de nuevo la fecha en
	std::tm* fecha_final = std::localtime(&fecha_en_segundos);
	// segundos a la estructura
	anno_=fecha_final->tm_year+1900;
	mes_=fecha_final->tm_mon+1;
	dia_=fecha_final->tm_mday;

	fecha_valida();

	return *this;
}

Fecha& Fecha::operator-= (int d){
	return *this += -d;
}

Fecha Fecha::operator+ (int d) const{
	Fecha temp{*this};
	return temp += d;
}
Fecha Fecha::operator- (int d) const{
	Fecha temp{*this};
	return temp += -d;
}

Fecha& Fecha::operator++ (){
	return *this += 1;
}

Fecha& Fecha::operator-- (){
	return *this += -1;
}

Fecha Fecha::operator++ (int){
	Fecha temp{*this};
	++*this;
	return temp;
}

Fecha Fecha::operator-- (int){
	Fecha temp{*this};
	--*this;
	return temp;
}

long operator-(const Fecha& f1, const Fecha& f2){
	std::tm tiempo_desde_1900_f1 = {};
	tiempo_desde_1900_f1.tm_year=f1.anno()-1900;
	tiempo_desde_1900_f1.tm_mon=f1.mes()-1;
	tiempo_desde_1900_f1.tm_mday=f1.dia();
	std::time_t fecha_en_segundos_f1 = std::mktime(&tiempo_desde_1900_f1);

	std::tm tiempo_desde_1900_f2 = {};
	tiempo_desde_1900_f2.tm_year=f2.anno()-1900;
	tiempo_desde_1900_f2.tm_mon=f2.mes()-1;
	tiempo_desde_1900_f2.tm_mday=f2.dia();
	std::time_t fecha_en_segundos_f2 = std::mktime(&tiempo_desde_1900_f2);

	return (fecha_en_segundos_f1-fecha_en_segundos_f2)/86400;
}

bool operator== (const Fecha& f1, const Fecha& f2){
	return (f1.anno()==f2.anno() && f1.mes()==f2.mes() && f1.dia()==f2.dia());
}

bool operator!= (const Fecha& f1, const Fecha& f2){
	return !(f1==f2);
}

bool operator< (const Fecha& f1, const Fecha& f2){
	if(f1.anno()<f2.anno()){ return true;}
	if(f1.anno()>f2.anno()){ return false;}
	// Entonces años iguales
	if(f1.mes()<f2.mes()){ return true;}
	if(f1.mes()>f2.mes()){ return false;}
	// Entonces meses iguales
	return f1.dia()<f2.dia();

}

bool operator> (const Fecha& f1, const Fecha& f2){
	return f2<f1;
}

bool operator<= (const Fecha& f1, const Fecha& f2){
	return !(f2<f1);
}

bool operator>= (const Fecha& f1, const Fecha& f2){
	return !(f1<f2);
}

////////////////FECHA VALIDA////////////////
void Fecha::fecha_valida() const{
	if((anno_<Fecha::AnnoMinimo || Fecha::AnnoMaximo<anno_) && (anno_!=0))
		throw Invalida("Año invalido. El año tiene que estar entre 1902 y 2037.");

	if((mes_<1 || 12<mes_) && (mes_!=0))
		throw Invalida("Mes invalido. El año tiene que estar entre 1 y 12.");

	if(mes_==1||mes_==3||mes_==5||mes_==7||mes_==8||mes_==10||mes_==12){
		if(dia_<1 || 31<dia_) throw Invalida("Éste mes solo tiene 31 dias");
  }else{
    	if(mes_==4||mes_==6||mes_==9||mes_==11){
    		if(dia_<1 || 30<dia_) throw Invalida("Éste mes solo tiene 30 dias");
    	}else{
      		if(anno_%4==0&&(anno_%400==0||anno_%100!=0)){
						if(dia_<1 || 29<dia_)
							throw Invalida("Es año bisiesto. Febrero tiene 29 dias.");
      		}else{
      			if(dia_<1 || 28<dia_)
							throw Invalida("No es año bisiesto. Febrero tiene 28 dias.");
      		}
	    }
	}
}
