#include "database.h"
#include "data_manager.h"
#include "pesos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cmath>
#include <filesystem>
using namespace std;
#define esquemas "Esquemas"
#define tamanio_sector 1000 // 10000 bits

//bool Database::validate(string nombre_relacion, string archivo_relacion) {
    // string linea_esquema;
    // ifstream archivo_entrada(esquemas); //archivo esquemas -> Estudiantes#nombre#string#id#int#dpto#string
    // vector <string> elementos; // ["string", "int", "string"]
    // int pos;
    // while(getline(archivo_entrada, linea_esquema)){
    //     string palabra_linea_esquema;
    //     istringstream linea_esquema_stream(linea_esquema);
    //     pos = linea_esquema.find(nombre_relacion);
    //     if (pos == 0) {
    //         while (getline(linea_esquema_stream, palabra_linea_esquema, '#')) {
    //             if (pos > 1 && pos % 2 == 0) {
    //                 elementos.push_back(palabra_linea_esquema);
    //             }
    //             pos++;
    //         }
    //         break;
    //     }
    // }

    // if (pos == -1) return false;

    // string linea_data_relacion;
    // ifstream data_relacion(archivo_relacion);
    // int pos_linea = 0;
    // while(getline(data_relacion, linea_data_relacion)) {
    //     if (pos_linea == 0) {
    //         pos_linea++;
    //         continue;
    //     }
    //     vector<string> types = get_type_from_line(linea_data_relacion); // ["string", "int", "string"]
    //     if (!(elementos == types)) return false;
    // }
//     return true;
// }

void Database::init() {
    string commands;
    cout<<" % MEGATRON3000 %"<<endl<<endl;
    cout<<"   WELCOME TO MEGATRON 3000!"<<endl<<endl;
    cout<<" Write the command to realize:"<<endl<<endl;
    while(true){
        cin>>commands;
        if(commands == "create_esquema")
            SchemaManager::create_esquema();
        else if(commands == "create_relacion")
            SchemaManager::create_relacion();
        else if(commands == "SELECT*FROM") { //SELECT*FROM Titanic
            string nombre_relacion;
            cin >> nombre_relacion;
            DataManager::consultas_datos(nombre_relacion);
        }
        else if(commands == "SELECT*FROM_") { //SELECT*FROM_ Estudiantes WHERE id < 64
            string nombre_relacion;
            string string_id;
            string operador;
            string separator;
            string nombre_nueva_relacion;
            int dato_operador;
            cin >> nombre_relacion;
            cout<< "WHERE" << " ";
            cin >> string_id;
            cin >> operador;
            cin >> dato_operador;
            cin >> separator;
            if(separator == "NULL"){
                cout << endl;
                DataManager::where(nombre_relacion, string_id, operador , dato_operador ); cout << endl; 
            }else if(separator == "|"){
                cout << endl;
                cin >> nombre_nueva_relacion; cout << endl;
                DataManager::where_condition(nombre_relacion, string_id, operador, dato_operador, separator, nombre_nueva_relacion); cout<< endl;
            }
        }
        else if(commands == "SELECT") { 
            string nombre_relacion;
            vector<string> columnas;
            string columna;
            while (cin >> columna){
                if (columna == "FROM") break;
                columnas.push_back(columna);
            }
            cin >> nombre_relacion;
            DataManager::consultas_tablas_final(nombre_relacion, columnas);
        }
        else if(commands == "new_register") {           
            string nombre_registro;
            int cant_platos, cant_superficies, cant_pistas, cant_sectores;
            cin >> nombre_registro;
            ifstream archivo("data_disco");
            archivo >> cant_platos >> cant_superficies >> cant_pistas >> cant_sectores;
            archivo.close();
            cout << cant_platos << " " << cant_superficies << " " << cant_pistas << " " << cant_sectores << endl;
            SchemaManager::new_register(nombre_registro, cant_platos, cant_superficies, cant_pistas, cant_sectores); 
        }
        else if (commands == "directory") {
            int cant_platos, cant_superficies, cant_pistas, cant_sectores;
            string register_data;
            cout << "Search?" << endl; cin >> register_data;
            ifstream archivo("data_disco");
            archivo >> cant_platos >> cant_superficies >> cant_pistas >> cant_sectores;
            archivo.close();
            SchemaManager::dictionary_search(register_data, cant_platos, cant_superficies, cant_pistas, cant_sectores);
        }
        else if (commands == "disk_space") {
            int cant_platos, cant_superficies, cant_pistas, cant_sectores;
            ifstream archivo("data_disco");
            archivo >> cant_platos >> cant_superficies >> cant_pistas >> cant_sectores;
            archivo.close();
            Peso::peso_disco( cant_platos, cant_superficies, cant_pistas, cant_sectores);
        }
        else if (commands == "create_bloque")
        {
            int cant_platos, cant_superficies, cant_pistas, cant_sectores, tamanioBloque;
            ifstream archivo("data_disco");
            archivo >> cant_platos >> cant_superficies >> cant_pistas >> cant_sectores;
            archivo.close();
            DataManager::Bloque(tamanioBloque, cant_platos, cant_superficies, cant_pistas, cant_sectores);
        }
        else if(commands == "exit")
            break;
        else
            cout<<"Not command"<<endl;
    }
}
