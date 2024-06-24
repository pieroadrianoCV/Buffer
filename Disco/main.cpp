#include "./Disco.cpp"
#include <iostream>
#include <vector>

int main() {
    bool discoCreado = false;
    Disco discoSimulado;
    int opcion;
    do {
        cout << "----------- Menu Disco ------------" << endl;
        cout << "1. Crear Disco" << endl;
        cout << "2. Eliminar Disco" << endl;
        cout << "Opcion? " << endl;
        cin >> opcion;

        switch (opcion){
            case 1: {
                if (!discoCreado) {
                    int platos;
                    int pistas;
                    int sectores;
                    int bytesPorSector;
                    int capacidadBloque;

                    cout << "Danos los datos necesarios para crear el Disco: " << endl << endl;
                    cout << "Cantidad de Platos: ";
                    cin >> platos;
                    cout << "Cantidad de Pistas por Superficie: ";
                    cin >> pistas;
                    cout << "Cantidad de Sectores por Pista: ";
                    cin >> sectores;
                    cout << "Cantidad de Bytes que habrá por Sector: ";
                    cin >> bytesPorSector;
                    
                    discoSimulado.setNumPlatos(platos);
                    discoSimulado.setPistasPorSuperficie(pistas);
                    discoSimulado.setSectorPorPista(sectores);
                    discoSimulado.setBytesPorSector(bytesPorSector);

                    discoSimulado.crear();

                    cout << "Capacidad del Bloque: ";
                    cin >> capacidadBloque;


                    string archivo;
                    cout << "Archivo para sectores: ";
                    cin >> archivo;
                    discoSimulado.llenarRegistrosEnSector(archivo);

                    discoSimulado.crearBloques(capacidadBloque, bytesPorSector, sectores);

                }
                else {
                    cout << "Ya hay disco existente." << endl;
                }
                break;
            }
            case 2: {
                discoSimulado.eliminarDisco();
                discoCreado = false;
                break;
            }
        }
    } while (opcion != 2);

    return 0;
}