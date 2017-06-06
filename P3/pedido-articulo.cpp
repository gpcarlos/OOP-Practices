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

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned c){
  LineaPedido x(pr,c);
  Directa[&p].insert(std::make_pair(&a, LineaPedido(pr, c)));
  Inversa[&a].insert(std::make_pair(&p, LineaPedido(pr, c)));
}
void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double pr, unsigned c){
  pedir(p,a,pr,c);
}

std::ostream& operator<< (std::ostream& os, const Pedido_Articulo::ItemsPedido& x){
  double importet_=0.0;
  os << "  PVP\t Cantidad\t\t\tArtículo\n"
     << "==============================================================\n";
  for (auto i : x){
    os << " " << std::fixed << std::setprecision(2) << i.second.precio_venta()
       << " € " << i.second.cantidad() << "\t\t\t[" << i.first->referencia() << "] \""
       << i.first->titulo() << "\"\n";
    importet_+=(i.second.precio_venta()*i.second.cantidad());
  }
  os << "==============================================================\n"
     << "Total   " << importet_ << " €\n";

  return os;
}

std::ostream& operator<< (std::ostream& os, const Pedido_Articulo::Pedidos& x){
  double importet_=0.0;
  double cantidadt_=0;

  os << "[Pedidos: "<< x.size() << "]\n"
     << "==============================================================\n"
     << "  PVP\t Cantidad\t\tFecha de venta\n"
     << "==============================================================\n";
  for (auto i : x){
    os << " " << std::fixed << std::setprecision(2) << i.second .precio_venta()
       << " € " << i.second.cantidad() << "\t\t\t" << i.first->fecha() << "\n";
    importet_+=(i.second.precio_venta()*i.second.cantidad());
    cantidadt_+=i.second.cantidad();
  }
  os << "==============================================================\n"
     << importet_ << " €\t" << std:: setprecision(0) << cantidadt_ << "\n";

  return os;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
  double importet_=0;
  for(auto i : Directa){
    os << "Pedido núm. " << i.first->numero() << std::endl
       << "Cliente: " << i.first->tarjeta()->titular()->nombre()
       << "\t\tFecha: " << i.first->fecha() << std::endl
       << i.second << std::endl;
    importet_+= i.first->total();
  }
  os << "TOTAL VENTAS\t" << std::fixed << std::setprecision(2) << importet_ << " €\n";
  return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
  for(auto i : Inversa){
    os << "Ventas de " << "[" << i.first->referencia() << "] \""
       << i.first->titulo() << "\"\n" << i.second << std::endl;
  }
  return os;
}
