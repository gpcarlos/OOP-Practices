/**
 * Programación Orientada a Objetos
 * Práctica 3: Clases de asociación y algoritmos de la STL
 * pedido-articulo.hpp
 *
 * @author: Carlos Gallardo Polanco
 * @version: 1.0
 */

#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iomanip>
#include <map>
#include <set>

class Pedido;
class Articulo;

class LineaPedido{
  public:

    ////////////////CONSTRUCTOR////////////////
    explicit LineaPedido(double pv, unsigned cv=1u): precio_venta_(pv),
      cantidad_vendida_(cv){}

    ////////////////OBSERVADORES////////////////
    double precio_venta() const noexcept{ return precio_venta_;}
    unsigned cantidad() const noexcept{ return cantidad_vendida_;}

  private:
    double precio_venta_;
    unsigned cantidad_vendida_;
};

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator<< (std::ostream& os, const LineaPedido& lp);


struct OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool>{
  bool operator()(const Pedido* p1, const Pedido* p2) const noexcept;
};

struct OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool>{
  bool operator()(const Articulo* a1, const Articulo* a2) const noexcept;
};

class Pedido_Articulo{
  public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

    ////////////////PEDIR////////////////
    void pedir(Pedido& p, Articulo& a, double pr, unsigned c=1);
    void pedir(Articulo& a, Pedido& p, double pr, unsigned c=1);

    ////////////////DETALLE////////////////
    const ItemsPedido& detalle(Pedido& p) const noexcept
    { return Directa.find(&p)->second;}

    ////////////////VENTAS////////////////
    const Pedidos& ventas(Articulo& a) const noexcept
    { return Inversa.find(&a)->second;}

    ////////////////MOSTRAR...////////////////
    std::ostream& mostrarDetallePedidos(std::ostream& os);
    std::ostream& mostrarVentasArticulos(std::ostream& os);

  private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> Directa;
    std::map<Articulo*, Pedidos, OrdenaArticulos> Inversa;

};

////////////////OPERADOR DE INSERCIÓN////////////////
std::ostream& operator<< (std::ostream& os, const Pedido_Articulo::ItemsPedido& x);
std::ostream& operator<< (std::ostream& os, const Pedido_Articulo::Pedidos& x);

#endif
