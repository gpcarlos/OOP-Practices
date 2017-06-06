/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * pedido-articulo.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "pedido-articulo.hpp"
#include "pedido.hpp"

/************************LINEAPEDIDO************************/

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator<< (std::ostream& os, const LineaPedido& l){
  os << std::fixed << std::setprecision(2) << l.precio_venta()
     << " €\t" << l.cantidad();
  return os;
}

/************************PEDIDO_ARTICULO************************/

bool OrdenaPedidos::operator()(const Pedido* p1, const Pedido* p2)
  const noexcept{ return p1->numero() < p2->numero();}

bool OrdenaArticulos::operator()(const Articulo* a1, const Articulo* a2)
  const noexcept{ return a1->referencia() < a2->referencia();}

////////////////PEDIR////////////////
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned c){
  Directa[&p].insert(std::make_pair(&a, LineaPedido(pr, c)));
  Inversa[&a].insert(std::make_pair(&p, LineaPedido(pr, c)));
  // Podría usarse 'Directa[&p][&a]= LineaPedido(pr, c)' si hubiera
  // constructor por defecto para LineaPedido
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double pr, unsigned c){
  pedir(p,a,pr,c);
}

////////////////MOSTRAR...////////////////
std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
  double importet_=0;

  for(auto i : Directa){
    os << "Pedido núm. " << i.first->numero() << "\n"
       << "Cliente: " << i.first->tarjeta()->titular()->id()
       << "\t\tFecha: " << i.first->fecha() << "\n" << i.second << "\n";
    importet_+= i.first->total();
  }
  os << "TOTAL VENTAS\t" << std::fixed << std::setprecision(2)
     << importet_ << " €\n";

  return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
  for(auto i : Inversa){
    os << "Ventas de " << "[" << i.first->referencia() << "] \""
       << i.first->titulo() << "\"\n" << i.second << "\n";
  }
  return os;
}

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator<< (std::ostream& os, const Pedido_Articulo::ItemsPedido& x){
  double importet_=0.0;

  os << "  PVP\t    Cantidad\t\tArtículo\n"
     << "===================================================================\n";
  for (auto i : x){
    os << " " << i.second << "\t\t[" << i.first->referencia()
       << "] \"" << i.first->titulo() << "\"\n";
    importet_+=(i.second.precio_venta()*i.second.cantidad());
  }
  os << "===================================================================\n"
     << "Total   " << std::fixed << std::setprecision(2) << importet_ << " €\n";

  return os;
}

std::ostream& operator<< (std::ostream& os, const Pedido_Articulo::Pedidos& x){
  double importet_=.0;
  double cantidadt_=0;

  os << "[Pedidos: "<< x.size() << "]\n"
     << "=============================================================\n"
     << "  PVP\t    Cantidad\t\tFecha de venta\n"
     << "=============================================================\n";
  for (auto i : x){
    os << " " << i.second << "\t\t" << i.first->fecha() << "\n";
    importet_+=(i.second.precio_venta()*i.second.cantidad());
    cantidadt_+=i.second.cantidad();
  }
  os << "=============================================================\n"
     << std::fixed << std::setprecision(2) << importet_ << " €\t"
     << std::setprecision(0) << cantidadt_ << "\n";

  return os;
}
