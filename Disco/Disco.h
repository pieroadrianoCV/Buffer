#ifndef DISCO_H
#define DISCO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Bloque {
    private:
        int Tamanio;
        string direccion;
    public:
        void establecerTamanio(int Tamanio) {
            this->Tamanio = Tamanio;
        }
        int tamanioBloque() const {
            return this->Tamanio;
        }
        void establecerDireccion(const string& direccion) {
            this->direccion += direccion + "\n";
        }
        void restarTamanio(int Tamanio) {
            this->Tamanio = Tamanio;
        }
        string imprimirDireccion() const {
            return direccion;
        }
};
class Disco {
    private:
        int numPlatos;
        int pistasPorSuperficie;
        int sectorPorPista;
        int bytesPorSector;
        vector<Bloque> bloques;
    public:
        Disco() {}
        Disco(int platos, int pistas, int sectores, int bytes) : 
            numPlatos(platos), pistasPorSuperficie(pistas), sectorPorPista(sectores), bytesPorSector(bytes) {}

        /* Funciones para obtener los Platos, Pistas, Sectores y Bytes de cada Sector */
        void setNumPlatos(int platos);
        void setPistasPorSuperficie(int pistas);
        void setSectorPorPista(int sector);
        void setBytesPorSector(int bytes);

        /*Funciones para la Estructura del Disco */
        void crearCarpeta(const string& rutaCarpeta);
        void crearArchivo(const string& rutaArchivo);

        /* Funcion para crear el Disco */
        void crear();
        
        /* Funcion para calcular la capacidad del disco en su totalidad */

        void capacidad();

        /* Funcion para eliminar el Disco */
        void eliminarDisco();

        /* Funciones para Registros en los sectores */
        void insertarRegistrosEnSector(ofstream& archivoSector, ifstream& archivoTexto, int registrosSector);
        void llenarRegistrosEnSector(const string& archivo);
        bool leerSector(const string& sector, string& contenido);

        /* Funciones para los Bloques del Disco */
        void crearBloques(int tamanoBloque, int tamanoSector, int cantidadDeSectores);
        void crearBloque();
        int calcularEspacioDisponibleEnBloque(const string& archivoBloque, int tamanoBloque);
        string obtenerRutaBloque(int numPlato, int numSuperficie, int numPista, int numBloque);
        bool validarDireccion(int plato, int superficie, int pista, int bloque);
        void mostrarContenidoBloque(const string& direccionBloque);
};

#endif
