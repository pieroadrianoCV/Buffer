/*
#include "./Bloque.h"

void Bloque::establecerTamanio(int tamanio) {
    this->tamanio = tamanio;
}

int Bloque::tamanio() const{
    return this->tamanio;
}

void Bloque::establecerDireccion(const string& direccion) {
    this->direccion += direccion + "\n";
}

void Bloque::restarTamanio(int tamanio) {
    this->tamanio -= tamanio;
}

string Bloque::imprimirDireccion() const {
    return direccion;
}

void bloques(int sectores, int sectoresTotales, vector<Bloque>& bloques, int tamanioPorSector) {
    int totalSectores = sectoresTotales;
    int cantidadBloques = (sectores + sectores - 1) / sectores;

    bloques.resize(cantidadBloques);

    for (int i = 0; i < cantidadBloques; i++) {
        bloques[i].establecerTamanio(tamanioPorSector * sectores);
    }

    for (int i = 0; i < cantidadBloques; i++) {
        cout << "Bloque: " << i << " tiene " << bloques[i].tamanio() << " espacio." << endl;
    }
}
*/