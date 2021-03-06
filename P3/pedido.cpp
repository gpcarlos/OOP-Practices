/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * pedido.cpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

/************************PEDIDO************************/

unsigned Pedido::total_pedidos_=0;

 ////////////////CONSTRUCTOR////////////////
Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& u,
   const Tarjeta& t, const Fecha& f): numero_(total_pedidos_+1),
   tarjeta_(&t), fecha_(f), importe_(.0){

  if(u.n_articulos()==0) throw Vacio(u);
  if(&u != t.titular()) throw Impostor(u);
  if(t.caducidad()<f) throw Tarjeta::Caducada(t.caducidad());

  for(auto c : u.compra()){ // c es un pair<Articulo*, unsigned>
    if(c.first->stock()<c.second){
      // es necesario el const_cast para quitarle a c el const
      const_cast<Usuario::Articulos&>(u.compra()).clear();
      throw SinStock(*c.first);
    }
  }

  // Necesitamos crear carro para que el iterador no falle,
  // ya que dentro del bucle, u es modificado
  Usuario::Articulos carro = u.compra();
  for(auto c :carro){
    Articulo *art_ = c.first;
    unsigned cantidad = c.second;
    double precio = art_->precio();
    art_->stock() -= cantidad;
    p_a.pedir(*this, *art_, precio, cantidad);
    importe_ += precio * cantidad;
    u.compra(*art_, 0);
  }

  u_p.asocia(u, *this);
  ++total_pedidos_;
}

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator<< (std::ostream& os, const Pedido& p){
  os << "Núm. pedido: " << p.numero() << "\n"
     << "Fecha:       " << p.fecha() << "\n"
     << "Pagado con:  " << p.tarjeta()->tipo() << " n.º: "
     << p.tarjeta()->numero() << "\n"
     << "Importe:     " << std::fixed << std::setprecision(2)
     << p.total() << " €" << "\n";
  return os;
}
