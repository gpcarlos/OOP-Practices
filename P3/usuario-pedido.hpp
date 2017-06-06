/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * usuario-pedido.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include "pedido.hpp"
#include <set>

class Usuario;
//class Pedido;

class Usuario_Pedido{
  public:
    typedef std::set<Pedido*> Pedidos;

    void asocia(Usuario& u, Pedido& p){
      Directa[&u].insert(&p);
      Inversa[&p]=&u;
    }
    void asocia(Pedido& p, Usuario& u){ asocia(u,p);}

    const Pedidos& pedidos(Usuario& u) const noexcept
    { return Directa.find(&u)->second;}
    const Usuario* cliente(Pedido& p) const noexcept
    { return Inversa.find(&p)->second;}

  private:
    std::map<Usuario*, Pedidos> Directa;
    std::map<Pedido*, Usuario*> Inversa;

};

#endif
