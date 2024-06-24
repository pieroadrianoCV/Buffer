#include "./Disco.h"
#include <filesystem>
namespace fs = std::filesystem;

int calcularTamanoRegistro(const string& linea) {
    int tamano = 0;
    stringstream ss(linea);
    string campo;
    while (getline(ss, campo, ',')) {
        if (campo != "NULL") {
            if (isdigit(campo[0])) {
                size_t posPunto = campo.find('.');
                if (posPunto != string::npos) {
                    tamano += 4;
                }
                else {
                    tamano += 4;
                }
            }
            else {
                tamano += campo.length();
            }
        }
    }
    return tamano;
}

void Disco::setNumPlatos(int platos) {
    this->numPlatos = platos;
    return;
}

void Disco::setPistasPorSuperficie(int superficie) {
    this->pistasPorSuperficie = superficie;
    return;
}

void Disco::setSectorPorPista(int sector) {
    this->sectorPorPista = sector;
    return;
}

void Disco::setBytesPorSector(int bytes) {
    this->bytesPorSector = bytes;
    return;
}

void Disco::crearCarpeta(const string& rutaCarpeta) {
    fs::create_directories(rutaCarpeta);
}

void Disco::crearArchivo(const string& rutaArchivo) {
    ofstream file(rutaArchivo);
    file.close();
}

void Disco::crear() {
    cout << "--------------- Creacion del Disco ---------------" << endl;
    string carpeta = "Disco";
    crearCarpeta(carpeta);

    for (int platos = 1; platos <= numPlatos; platos++) {
        string carpetaPlato = carpeta + "/Plato " + to_string(platos);
        crearCarpeta(carpetaPlato);
        for (int superficies = 1; superficies <= 2; superficies++) {
            string carpetaSuperficie = carpetaPlato + "/Superficie " + to_string(superficies);
            crearCarpeta(carpetaSuperficie);
            for (int pistas = 1; pistas <= pistasPorSuperficie; pistas++) {
                string carpetaPista = carpetaSuperficie + "/Pista " + to_string(pistas);
                crearCarpeta(carpetaPista);
                for (int sectores = 1; sectores <= sectorPorPista; sectores++) {
                    string archivoSector = carpetaPista + "/" + to_string(sectores) + ".txt";
                    crearArchivo(archivoSector);
                }
            }
        }
    }
    ofstream archivo("../megatron2/data_disco");
    archivo << numPlatos << endl;
    archivo << 2 << endl;
    archivo << pistasPorSuperficie << endl;
    archivo << sectorPorPista << endl;
    archivo.close();
}

void Disco::capacidad() {
    cout << "--------------- Capacidad del Disco Creado ---------------" << endl;
    cout << endl;
    cout << "Capacidad: " << this->bytesPorSector * this->sectorPorPista * this->pistasPorSuperficie * 2 * this->numPlatos
    << " bytes en total."<< endl; 
}

void Disco::eliminarDisco() {
    string carpeta = "Disco";
    if (fs::exists(carpeta)) {
        fs::remove_all(carpeta);
        cout << "Disco eliminado correctamente." << endl;
    }
    else {
        cout << "No existe un Disco creado, debe crear el disco primero." << endl;
    }
}

void Disco::insertarRegistrosEnSector(ofstream& archivoSector, ifstream& archivoTexto, int registrosPorSector) {
    for (int i = 0; i < registrosPorSector; ++i) {
        string linea;
        if (getline(archivoTexto, linea)) {
            archivoSector << linea << endl;
        }
    }
    cout << endl;
}

void Disco::llenarRegistrosEnSector(const string& archivo) {
    string path = "../static/" + archivo;
    ifstream archivoTxt(path);
    if (!archivoTxt.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivoTxt, linea)) {
        int tamanoRegistro = calcularTamanoRegistro(linea);
        int bytes = this->bytesPorSector;
        int registrosSector = bytes / tamanoRegistro;

        for (int platos = 1; platos <= this->numPlatos; platos++) {
            for (int superficies = 1; superficies <= 2; superficies++) {
                for (int pistas = 1; pistas <= this->pistasPorSuperficie; pistas++) {
                    for (int sectores = 1; sectores <= this->sectorPorPista; sectores++) {
                        string carpetaPista = "Disco/Plato " + to_string(platos) + "/Superficie " +
                                            to_string(superficies) + "/Pista " + to_string(pistas);
                        string archivoSector = carpetaPista + "/" + to_string(sectores) + ".txt";
                        ofstream archivoSectorEscritura(archivoSector, ios::app);
                        insertarRegistrosEnSector(archivoSectorEscritura, archivoTxt, registrosSector);
                        archivoSectorEscritura.close();
                    }
                }
            }
        }
    }

    archivoTxt.close();
}

bool Disco::leerSector(const string& sector, string& contenido) {
    cout << "Intentando leer sector desde: " << sector << endl;
    ifstream archivo(sector);
    if (archivo.is_open()) {
        cout << "Archivo del sector abierto correctamente." << endl;
        stringstream buffer;
        buffer << archivo.rdbuf();
        contenido = buffer.str();
        archivo.close();
        cout << "Contenido del sector leído: " << contenido << endl;
        return true;
    } else {
        cout << "No se pudo abrir el archivo del sector: " << sector << endl;
    }
    return false;
}

int Disco::calcularEspacioDisponibleEnBloque(const string& archivoBloque, int tamanoBloque) {
    ifstream archivo(archivoBloque);
    if (!archivo.is_open()) {
        cerr << "No se puede abrir el archivo: " << archivoBloque << endl;
    }

    int tamanioUtilizado = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.rfind("Plato:", 0) == 0 || linea.find("===") != string::npos || linea.find("-----------------------") != string::npos) {
            continue;
        }
        tamanioUtilizado += linea.size() + 1;
    }

    archivo.close();

    int espacioDisponible = tamanoBloque - tamanioUtilizado;
    return espacioDisponible;
}

/*
void Disco::crearBloques(int tamanoBloque, int tamanoSector, int cantidadDeSectores) {
    int sectoresPorBloque = tamanoBloque / tamanoSector;
    cout << "Cantidad de Sectores por Bloque: " << sectoresPorBloque << endl;
    int cantidadBloques = (cantidadDeSectores + sectoresPorBloque - 1) / sectoresPorBloque;
    cout << "Cantidad de Bloques a crear: " << cantidadBloques << endl;

    vector<Bloque> bloques(cantidadBloques);
    int contadorBloqueGlobal = 1;  // Contador global para la numeración consecutiva de bloques

    for (int platos = 1; platos <= numPlatos; platos++) {
        for (int superficies = 1; superficies <= 2; superficies++) {
            for (int pistas = 1; pistas <= pistasPorSuperficie; pistas++) {
                string carpetaPista = "Disco/Plato " + to_string(platos) + "/Superficie " +
                                      to_string(superficies) + "/Pista " + to_string(pistas);
                for (int sector = 1; sector <= sectorPorPista; sector += sectoresPorBloque) {
                    // Usar el contador global para la numeración del bloque
                    string carpetaDirectorio = "../megatron2/directorio";
                    ofstream directorio(carpetaDirectorio, ios::app);
                    directorio << platos << "/" << superficies << "/" << pistas << "/" << contadorBloqueGlobal << endl;
                    string archivoBloque = carpetaPista + "/Bloque " + to_string(contadorBloqueGlobal) + ".txt";
                    ofstream archivo(archivoBloque, ios::app);
                    if (archivo.is_open()) {
                        archivo << "Plato: " << platos << " Superficie: " << superficies << " Pista: " << pistas << " Bloque: " << contadorBloqueGlobal << endl;
                        archivo << "=====================================================" << endl;
                        for (int i = 0; i < sectoresPorBloque; i++) {
                            int sectorActual = sector + i;
                            if (sectorActual <= sectorPorPista) {
                                string archivoSector = carpetaPista + "/" + to_string(sectorActual) + ".txt";
                                string contenido;
                                if (leerSector(archivoSector, contenido)) {
                                    archivo << "Plato: " << platos << " Superficie: " << superficies << " Pista: " << pistas << " Sector: " << sectorActual << endl;
                                    archivo << contenido << endl;
                                } else {
                                    archivo << "Plato: " << platos << " Superficie: " << superficies << " Pista: " << pistas << " Sector: " << sectorActual << endl;
                                    archivo << "Sector vacío" << endl;
                                }
                                archivo << "-----------------------" << endl;
                            }
                        }
                        archivo.close();
                        cout << "Bloque Creado: " << archivoBloque << endl;
                        contadorBloqueGlobal++;  // Incrementar el contador global después de crear cada bloque
                    } else {
                        cerr << "No se pudo crear el Bloque: " << archivoBloque << endl;
                    }
                }
            }
        }
    }
}
*/


void Disco::crearBloques(int tamanoBloque, int tamanoSector, int cantidadDeSectores) {
    int sectoresPorBloque = tamanoBloque / tamanoSector;
    cout << "Cantidad de Sectores por Bloque: " << sectoresPorBloque << endl;
    int cantidadBloques = (cantidadDeSectores + sectoresPorBloque - 1) / sectoresPorBloque;
    cout << "Cantidad de Bloques a crear: " << cantidadBloques << endl;

    vector<Bloque> bloques(cantidadBloques);
    int contadorBloqueGlobal = 1;

    for (int platos = 1; platos <= numPlatos; platos++) {
        for (int superficies = 1; superficies <= 2; superficies++) {
            for (int pistas = 1; pistas <= pistasPorSuperficie; pistas++) {
                string carpetaPista = "Disco/Plato " + to_string(platos) + "/Superficie " +
                                      to_string(superficies) + "/Pista " + to_string(pistas);
                for (int sector = 1; sector <= sectorPorPista; sector += sectoresPorBloque) {
                    
                    string carpetaDirectorio = "../megatron2/directorio";
                    ofstream directorio(carpetaDirectorio, ios::app);
                    directorio << platos << "/" << superficies << "/" << pistas << "/" << contadorBloqueGlobal << endl;
                    string archivoBloque = carpetaPista + "/Bloque " + to_string(contadorBloqueGlobal) + ".txt";
                    ofstream archivo(archivoBloque, ios::app);
                    if (archivo.is_open()) {
                        archivo << "Plato: " << platos << " Superficie: " << superficies << " Pista: " << pistas << " Bloque: " << contadorBloqueGlobal << endl;
                        archivo << "=====================================================" << endl;

                        int espacioDisponible;
                        calcularEspacioDisponibleEnBloque(archivoBloque, tamanoBloque);

                        for (int i = 0; i < sectoresPorBloque; i++) {
                            int sectorActual = sector + i;
                            if (sectorActual <= sectorPorPista) {
                                string archivoSector = carpetaPista + "/" + to_string(sectorActual) + ".txt";
                                string contenido;
                                if (leerSector(archivoSector, contenido)) {
                                    //int tamanoContenido = contenido.size() + 1;
                                    //if (tamanoContenido <= espacioDisponible) {
                                        archivo << "Plato: " << platos << " Superficie: " << superficies << " Pista: " << pistas << " Sector: " << sectorActual << endl;
                                        archivo << contenido << endl;
                                        //espacioDisponible -= tamanoContenido;
                                    //}
                                    //else {
                                        //cerr << "No hay espacio suficiente en el Bloque." << endl;
                                    //}
                                }
                                else {
                                    archivo << "Plato: " << platos << " Superficie: " << superficies << " Pista: " << pistas << " Sector: " << sectorActual << endl;
                                    archivo << "Sector vacío" << endl;
                                }
                                archivo << "-----------------------" << endl;
                            }
                        }
                        archivo.close();
                        cout << "Bloque Creado: " << archivoBloque << endl;
                        espacioDisponible = calcularEspacioDisponibleEnBloque(archivoBloque, tamanoBloque);
                        cout << "Espacio disponible en el Bloque " << contadorBloqueGlobal << ": " << espacioDisponible << " bytes" << endl;
                        contadorBloqueGlobal++;
                    } else {
                        cerr << "No se pudo crear el Bloque: " << archivoBloque << endl;
                    }
                }
            }
        }
    }
}


string Disco::obtenerRutaBloque(int numPlato, int numSuperficie, int numPista, int numBloque) {
    return "../Disco/Plato " + to_string(numPlato) + "/Superficie " + to_string(numSuperficie) +
            "/Pista " + to_string(numPista) + "/Bloque " + to_string(numBloque) + ".txt";
}

bool Disco::validarDireccion(int plato, int superficie, int pista, int bloque) {
    string pathBloque = "Disco/Plato " + to_string(plato) + "/Superficie " + to_string(superficie) +
                        "/Pista " + to_string(pista) + "/Bloque " + to_string(bloque) + ".txt";
    return fs::exists(pathBloque);
}

void Disco::mostrarContenidoBloque(const string& direccionBloque) {
    ifstream archivo(direccionBloque);
    cout << "Contenido del Bloque " << direccionBloque << ": " << endl;
    string linea;
    while (getline(archivo,linea)) {
        cout << linea << endl;
    }
    archivo.close();
}