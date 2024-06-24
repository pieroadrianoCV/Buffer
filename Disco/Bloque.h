#ifndef BLOQUE_H
#define BLOQUE_H

#include <iostream>
using namespace std;

class Bloque {
    private:
        int tamanio;
        string direccion;
    public:
        void establecerTamanio(int tamanio);
        int tamanio() const;
        void establecerDireccion(const string& direccion);
        void restarTamanio(int tamanio);
        string imprimirDireccion() const;
};

#endif