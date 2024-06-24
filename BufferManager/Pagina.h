#ifndef PAGINA_H
#define PAGINA_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Pagina{
    public:
        vector<string> vectorRegistrosEnPagina;
    public:
        Pagina();
        ~Pagina();
        void recogerRegistros(int numPagina);
        void mostrarContenidoDePagina();
        bool verificarPaginaVacia();
        void leerOescribirEnPagina();
        void agregarContenido(int numPaginaEliminada);
};

#endif