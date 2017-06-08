/**
 * Programación Orientada a Objetos
 * Práctica 4: Herencia y polimorfismo
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
Pedido::Pedido( Usuario_Pedido& u_p, Pedido_Articulo& p_a,
  Usuario& u, const Tarjeta& t, const Fecha& f): numero_(total_pedidos_+1),
  tarjeta_(&t), fecha_(f), importe_(.0){

  if(u.n_articulos()==0){ throw Vacio(u);}
  if(&u != t.titular()){ throw Impostor(u);}
  if(t.caducidad()<f){ throw Tarjeta::Caducada(t.caducidad());}

  bool pedido_final_vacio = true;
  Usuario::Articulos carro = u.compra();

  for(auto i : carro ){
    Articulo* pa = i.first;
    unsigned cantidad = i.second;
    double precio = pa->precio();
    if (ArticuloAlmacenable* paa = dynamic_cast<ArticuloAlmacenable*>(pa)){
      if(paa->stock()<cantidad){
        const_cast<Usuario::Articulos&>(u.compra()).clear();
        throw SinStock(*pa);
      }
      paa->stock()-=cantidad;
      p_a.pedir(*this, *pa, precio, cantidad);
      importe_+=precio*cantidad;
      u.compra(*pa , 0);
      pedido_final_vacio=false;
    }else{
      if (LibroDigital* pdl = dynamic_cast<LibroDigital*>(pa)){
        if(pdl->f_expir() > f){
          p_a.pedir(*this, *pa, precio, cantidad);
          importe_ += precio*cantidad;
          u.compra(*pa , 0);
          pedido_final_vacio = false;
        }
      }
    }
  }
  if(pedido_final_vacio) throw Vacio(u);
  u_p.asocia(u, *this);
  total_pedidos_++;
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
