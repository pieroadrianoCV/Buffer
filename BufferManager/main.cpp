#include <iostream>
#include <queue>
#include "./BufferManager.cpp"
using namespace std;

struct Requerimiento {
    int numPagina;
    char accion;
};

queue<Requerimiento> colaDeRequerimientos;
//queue<Requerimiento> colaDeEspera;

/* Funcion para ver REQUERIMIENTOS incial*/

void visualizarCola() {
    queue<Requerimiento> tempCola = colaDeRequerimientos;
    cout << "Cola de Requerimientos:" << endl;
    if (tempCola.empty()) {
        cout << "La cola está vacía." << endl;
        return;
    }
    while (!tempCola.empty()) {
        Requerimiento req = tempCola.front();
        tempCola.pop();
        cout << "Pagina: " << req.numPagina << ", Accion: " << (req.accion == 'L' || req.accion == 'l' ? "Leer" : "Escribir") << endl;
    }
}

void procesarColaEscritura(int paginaLiberar) {
    queue<Requerimiento> tempCola;
    bool escrituraEncontrada = false;
    bool lecturaEncontrada = false;

    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();
        
        if (req.numPagina == paginaLiberar && (req.accion == 'W' || req.accion == 'w')) {
            cout << "Procesando Escritura en Pagina: " << req.numPagina << endl;
            escrituraEncontrada = true;
            break;
        } else {
            tempCola.push(req);
        }
    }

    if (escrituraEncontrada) {
        while (!tempCola.empty()) {
            colaDeRequerimientos.push(tempCola.front());
            tempCola.pop();
        }
        
        cout << "Cola actualizada después de liberar una escritura:" << endl;
        visualizarCola();
        return;
    }

    tempCola = queue<Requerimiento>();
    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();

        if (req.numPagina == paginaLiberar && (req.accion == 'L' || req.accion == 'l')) {
            cout << "Procesando Lectura en Pagina: " << req.numPagina << endl;
            lecturaEncontrada = true;
            break;
        } else {
            tempCola.push(req);
        }
    }

    if (!escrituraEncontrada && lecturaEncontrada) {
        cout << "Cola actualizada después de liberar una lectura:" << endl;
        while (!tempCola.empty()) {
            colaDeRequerimientos.push(tempCola.front());
            tempCola.pop();
        }
        visualizarCola();
    }

    if (!escrituraEncontrada && !lecturaEncontrada) {
        cout << "Cola original sin liberaciones:" << endl;
        visualizarCola();
    }
}

bool noEscrituraEnCola(int pagina) {
    queue<Requerimiento> tempCola = colaDeRequerimientos;
    while (!tempCola.empty()) {
        Requerimiento req = tempCola.front();
        tempCola.pop();
        if (req.numPagina == pagina && (req.accion == 'W' || req.accion == 'w')) {
            return false; 
        }
    }
    return true; 
}

void procesarColaLectura(int paginaLiberar) {
    queue<Requerimiento> tempCola;
    bool escrituraEncontrada = false;
    bool lecturaEncontrada = false;

    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();
        
        if (req.numPagina == paginaLiberar && (req.accion == 'L' || req.accion == 'l')) {
            cout << "Procesando Escritura en Pagina: " << req.numPagina << endl;
            escrituraEncontrada = true;
            break;
        } else {
            tempCola.push(req);
        }
    }

    if (escrituraEncontrada) {
        while (!tempCola.empty()) {
            colaDeRequerimientos.push(tempCola.front());
            tempCola.pop();
        }
        
        cout << "Cola actualizada después de liberar una escritura:" << endl;
        visualizarCola();
        return;
    }

    tempCola = queue<Requerimiento>();
    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();

        if (req.numPagina == paginaLiberar && (req.accion == 'L' || req.accion == 'l')) {
            cout << "Procesando Lectura en Pagina: " << req.numPagina << endl;
            lecturaEncontrada = true;
            break;
        } else {
            tempCola.push(req);
        }
    }

    if (!escrituraEncontrada && lecturaEncontrada) {
        cout << "Cola actualizada después de liberar una lectura:" << endl;
        while (!tempCola.empty()) {
            colaDeRequerimientos.push(tempCola.front());
            tempCola.pop();
        }
        visualizarCola();
    }

    if (!escrituraEncontrada && !lecturaEncontrada) {
        cout << "Cola original sin liberaciones:" << endl;
        visualizarCola();
    }
}

void menuBufferManager(BufferManager &bufferManagerPrincipal) {
    cout << "Bienvenido a implementación de BUFFER" << endl;
    int pesoBytesBLoque;
    cout << "Ingrese el peso de su bloque de Disco: " << endl;
    cin >> pesoBytesBLoque;
    int numFrames;
    cout << "Ingrese la cantidad de Frames a tener en el Buffer Pool: " << endl;
    cin >> numFrames;
    
    bufferManagerPrincipal.crearBufferPoolSegunNumFrames(numFrames);
    bufferManagerPrincipal.establecerLimiteDeFrames(pesoBytesBLoque);
    
    cout << "Creación de estructura Básica de BufferManager implementado." << endl;
}

void menu() {
    BufferManager bufferManagerPrincipal;
    int opcion = 0;
    int numPagina;
    int numFrame;
    int opcionPaginaGuardado;

    while (opcion != 9) {
        cout << endl;
        cout << "------- Menú Principal Programa Buffer Manager -------" << endl;
        cout << "1. Crear Buffer Pool" << endl;
        cout << "2. Obtener Una Página" << endl;
        cout << "3. Mostrar Page Table" << endl;
        cout << "4. Liberar uso de Página" << endl;
        cout << "5. Unpinnear Una Página" << endl;
        cout << "6. Visualizar Cola de Requerimientos" << endl;
        cout << "7. Mostrar contenido de una pagina" << endl;
        cout << "8. Salir del programa principal" << endl;
        cout << "Ingrese el numero de opcion" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1: {
                menuBufferManager(bufferManagerPrincipal);
                break;
            }
            case 2: {
                cout << "Ingrese el numero de pagina que desea OBTENER (Modo Prueba 1 - 6): " << endl;
                cin >> numPagina;
                bufferManagerPrincipal.obtenerUnaPagina(numPagina);
                
                char accionPagina;
                cout << "Leer (L/l) o Escribir (W/w) en Pagina?: ";
                cin >> accionPagina;

                //bool requerimientoAgregado = false;
                
                
                //cout << "Requerimiento agregado a la cola." << endl;

                numFrame = bufferManagerPrincipal.pageTable.getNumFrameDeUnaPagina(numPagina);

                if (accionPagina == 'L' || accionPagina == 'l') {
                    cout << "Proceso de Lectura." << endl;
                    if (bufferManagerPrincipal.pageTable.verificarDirtyPagina(numPagina) == false) {
                        bufferManagerPrincipal.bufferPool.mostrarFramePagina(numFrame);
                        bufferManagerPrincipal.pageTable.aumentarPinCountDePagina(numPagina);
                        if (noEscrituraEnCola(numPagina) == true)
                            {
                                Requerimiento req = {numPagina, accionPagina};
                                colaDeRequerimientos.push(req);
                                break;
                            }
                            else
                            {
                                cout << "No se puede añadir a la cola este proceso de lectura, hay uno de escritura en cola" << endl;
                                break;
                            }
                    }
                    else {
                        cout << "Dirty Bit de la Pagina " << numPagina << " esta en 1." << endl;
                        cout << "No se puede procesar el requerimiento de Lectura hasta que Dirty Bit sea 0." << endl;
                        cout << "Si se quiere procesar el requerimiento de Lectura, debe guardar el archivo." << endl;
                        cout << "Guardar contenido? 0/NO GUARDAR  1/GUARDAR: ";
                        cin >> opcionPaginaGuardado;

                        if (opcionPaginaGuardado == 0) {
                            cout << "No se guardo el archivo " << endl;
                            //Requerimiento colaEspera = {numPagina, accionPagina};
                            //colaDeEspera.push(colaEspera);
                            //requerimientoAgregado = true;
                        }
                        else if (opcionPaginaGuardado == 1) {
                            bufferManagerPrincipal.pageTable.cambiarDirtyBitDePagina(numPagina);
                            bufferManagerPrincipal.bufferPool.agregarContenidoPaginaAbloque(numFrame, numPagina);
                            bufferManagerPrincipal.pageTable.aumentarPinCountDePagina(numPagina);
                            Requerimiento req = {numPagina, accionPagina};
                            colaDeRequerimientos.push(req);
                                
                        }
                    }
                    break;
                }
                else if (accionPagina == 'W' || accionPagina == 'w') {
                    bufferManagerPrincipal.bufferPool.lecturaOescrituraPagina(numFrame);
                    bufferManagerPrincipal.pageTable.aumentarPinCountDePagina(numPagina);
                    
                    if (noEscrituraEnCola(numPagina) == true)
                    {
                        bufferManagerPrincipal.pageTable.cambiarDirtyBitDePagina(numPagina);
                        Requerimiento req = {numPagina, accionPagina};
                        colaDeRequerimientos.push(req);
                        break;
                    }
                    else
                    {
                        cout << "No se puede añadir a la cola este proceso de escritura, ya existe uno en espera" << endl;
                        break;
                    }
                    break;
                }

                /*
                if (!requerimientoAgregado) {
                    Requerimiento req = {numPagina, accionPagina};
                    colaDeRequerimientos.push(req);
                    cout << "Requerimiento agregado a la cola." << endl;
                }
                */

                //Requerimiento req = {numPagina, accionPagina};
                //colaDeRequerimientos.push(req);
                //cout << "Requerimiento agregado a la cola." << endl;
                break;
            }
            case 3: {
                bufferManagerPrincipal.mostrarPageTAble();
                cout << endl;
                break;
            }
            case 4: {
                cout << "Ingrese el numero de la pagina a liberar (descontar PinCount)" << endl;
                cin >> numPagina;

                if (bufferManagerPrincipal.pageTable.verificarDirtyPagina(numPagina) == true) {
                    cout << "Dirty = 1 " << endl;
                    cout << "Para continuar, desea guardar el contenido? 0/NO GUARDAR  1/GUARDAR" << endl;
                    int opcionPaginaGuardado;
                    cin >> opcionPaginaGuardado;

                    if (opcionPaginaGuardado == 0) {
                        cout << "Página no guardada, no se descuenta pin count." << endl;
                    } else if (opcionPaginaGuardado == 1) {
                        bufferManagerPrincipal.pageTable.cambiarDirtyBitDePagina(numPagina);
                        bufferManagerPrincipal.bufferPool.agregarContenidoPaginaAbloque(numFrame, numPagina);
                        bufferManagerPrincipal.pageTable.descontarPinCountApagina(numPagina);
                        procesarColaEscritura(numPagina);
                    } else {
                        cout << "Opción inválida" << endl;
                    }
                } else if (bufferManagerPrincipal.pageTable.verificarDirtyPagina(numPagina) == false) {
                    cout << "Dirty = 0 " << endl;
                    bufferManagerPrincipal.pageTable.descontarPinCountApagina(numPagina);
                    procesarColaLectura(numPagina);
                }
                
                break;
            }
            case 5: {
                cout << "Ingrese Pagina a Despinnear " << endl;
                cin >> numPagina;
                bufferManagerPrincipal.pageTable.unpinnearPagina(numPagina);
                break;
            }
            case 6: {
                visualizarCola();
                break;
            }
            case 7: {
                cout << "Ingrese pagina a visualizar " << endl;
                cin >> numPagina;
                bufferManagerPrincipal.mostrarUnaPagina(numPagina);
                break;
            }
            case 8: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default:
                cout << "Opción inválida, por favor intente de nuevo." << endl;
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}