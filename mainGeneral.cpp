#include <iostream>
#include <cstdlib> 
using namespace std;

void ejecutarBufferManager() {
    cout << "Ejecutando código de BufferManager..." << endl;
    system("cd BufferManager && ./main"); 
}

void ejecutarDisco() {
    cout << "Ejecutando código de Disco..." << endl;
    system("cd Disco && ./main"); 
}

void ejecutarMegatron() {
    cout << "Ejecutando código de Megatron..." << endl;
    system("cd megatron2 && ./MEGATRON"); 
}

int main() {
    int opcion;
    
    do {
        cout << "Seleccione una opción:" << endl;
        cout << "1. Ejecutar código de BufferManager" << endl;
        cout << "2. Ejecutar código de Disco" << endl;
        cout << "3. Ejecutar código de Megatron3" << endl;
        cout << "4. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ejecutarBufferManager();
                break;
            case 2:
                ejecutarDisco();
                break;
            case 3:
                ejecutarMegatron();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
