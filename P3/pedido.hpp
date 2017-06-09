/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * pedido.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "usuario.hpp"
#include "tarjeta.hpp"

class Usuario;
class Articulo;
class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
  public:
    class Vacio{
      public:
        Vacio(const Usuario& u): us_(&u){}
        const Usuario& usuario() const noexcept{ return *us_;}
      private:
        const Usuario* us_;
    };

    class Impostor{
      public:
        Impostor(const Usuario& u): us_(&u){}
        const Usuario& usuario() const noexcept{ return *us_;}
      private:
        const Usuario* us_;
    };

    class SinStock{
      public:
        SinStock(const Articulo& a): ar_(&a){}
        const Articulo& articulo() const noexcept{ return *ar_;}
      private:
        const Articulo* ar_;
    };

    ////////////////CONSTRUCTOR////////////////
    Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& u,
      const Tarjeta& t, const Fecha& f=Fecha());

    ////////////////OBSERVADORES////////////////
    int numero() const noexcept{ return numero_;}
    const Tarjeta* tarjeta() const noexcept{ return tarjeta_;}
    Fecha fecha() const noexcept{ return fecha_;}
    double total() const noexcept{ return importe_;}
    static unsigned n_total_pedidos() noexcept{return total_pedidos_;}

  private:
    int numero_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double importe_;
    static unsigned total_pedidos_;
};

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator<< (std::ostream& os, const Pedido& p);

#endif
