//Jonathan Samuel GOnzalez Ixpata
#include "Catalogo.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Bitacora.h"
#include "Usuario.h"
#include <cstring>
#include <iomanip>

using namespace std;

Bitacora bitacoralogCatalogo;

void Catalogo::setUsuario(const string& u) { usuario = u; }

void Catalogo::cargarPacientes() {
    pacientes.clear();
    ifstream file(archivo, ios::binary);
    if (!file) return;

    Paciente p;
    while (file.read(reinterpret_cast<char*>(&p), sizeof(Paciente))) {
        pacientes.push_back(p);
    }
    file.close();
    ordenarPacientes();
}

void Catalogo::guardarPacientes() {
    ofstream file(archivo, ios::binary | ios::trunc);
    for (const auto& p : pacientes) {
        file.write(reinterpret_cast<const char*>(&p), sizeof(Paciente));
    }
    file.close();
}

void Catalogo::ordenarPacientes() {
    sort(pacientes.begin(), pacientes.end(), [](const Paciente& a, const Paciente& b) {
        return strcmp(a.idPaciente, b.idPaciente) < 0;
    });
}

void Catalogo::menuCatalogo() {
    int opcion;
    do {
        Usuario::limpiarPantalla();
        cout << "Nombre: Jonathan Gonzales 9959-23-3184" << endl;
        cout << "Usuario: " << usuario << endl;
        cargarPacientes();
        cout << "\n=== MENU Usuario ===" << endl; //Menu Usuario
        cout << "1. Crear Usuario" << endl;
        cout << "2. Borrar Usuario" << endl;
        cout << "3. Buscar Usuario" << endl;
        cout << "4. Modificar Usuario" << endl;
        cout << "5. Desplegar Usuario" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: crearPaciente(); break;
            case 2: borrarPaciente(); break;
            case 3: buscarPaciente(); break;
            case 4: modificarPaciente(); break;
            case 5: desplegarPacientes(); Usuario::pausar(); break;
            case 6: return;
            default:
                cout << "Opcion invalida." << endl;
                Usuario::pausar();
        }
    } while (true);
}

void Catalogo::crearPaciente() {
    Paciente p;
    cout << "\n=== CREAR Usuario ===" << endl; //Crar usuario
    cout << "ID Usuario: ";
    cin.getline(p.idPaciente, sizeof(p.idPaciente));
    cout << "Nombre: ";
    cin.getline(p.nombre, sizeof(p.nombre));
    cout << "Apellido: ";
    cin.getline(p.apellido, sizeof(p.apellido));
    cout << "Correo: ";
    cin.getline(p.genero, sizeof(p.genero));
    cout << "Direccion: ";
    cin.getline(p.direccion, sizeof(p.direccion));
    cout << "Telefono: ";
    cin.getline(p.telefono, sizeof(p.telefono));

    pacientes.push_back(p);
    guardarPacientes();
    bitacoralogCatalogo.insertar(usuario, 2001, "Catalogo", "Crear Usuario");
    cout << "\nUsuario creado exitosamente." << endl;
    Usuario::pausar();
}

void Catalogo::borrarPaciente() {
    char id[20];
    cout << "\n=== BORRAR Usuario ===" << endl;
    cout << "ID Usuario a borrar: ";
    cin.getline(id, sizeof(id));

    auto it = remove_if(pacientes.begin(), pacientes.end(), [&](const Paciente& p) {
        return strcmp(p.idPaciente, id) == 0;
    });

    if (it != pacientes.end()) {
        pacientes.erase(it, pacientes.end());
        guardarPacientes();
        bitacoralogCatalogo.insertar(usuario, 2002, "Catalogo", "Borrar Usuario");
        cout << "Usuario borrado exitosamente." << endl;
    } else {
        cout << "Usuario no encontrado." << endl;
    }
    Usuario::pausar();
}

void Catalogo::buscarPaciente() {
    char id[20];
    cout << "\n=== BUSCAR Usuario ===" << endl;
    cout << "ID Usuario: ";
    cin.getline(id, sizeof(id));

    for (const auto& p : pacientes) {
        if (strcmp(p.idPaciente, id) == 0) {
            cout << "\nUsuario encontrado:" << endl;
            cout << "ID: " << p.idPaciente << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Apellido: " << p.apellido << endl;
            cout << "Correo: " << p.genero << endl;
            cout << "Direccion: " << p.direccion << endl;
            cout << "Telefono: " << p.telefono << endl;
            bitacoralogCatalogo.insertar(usuario, 2003, "Catalogo", "Buscar Usuario");
            Usuario::pausar();
            return;
        }
    }
    cout << "Usuario no encontrado." << endl;
    Usuario::pausar();
}

void Catalogo::modificarPaciente() {
    char id[20];
    cout << "\n=== MODIFICAR Usuario ===" << endl;
    cout << "ID Usuario: ";
    cin.getline(id, sizeof(id));

    for (auto& p : pacientes) {
        if (strcmp(p.idPaciente, id) == 0) {
            cout << "Nuevo Nombre: ";
            cin.getline(p.nombre, sizeof(p.nombre));
            cout << "Nuevo Apellido: ";
            cin.getline(p.apellido, sizeof(p.apellido));
            cout << "Nuevo Correo: ";
            cin.getline(p.genero, sizeof(p.genero));
            cout << "Nueva Direccion: ";
            cin.getline(p.direccion, sizeof(p.direccion));
            cout << "Nuevo Telefono: ";
            cin.getline(p.telefono, sizeof(p.telefono));

            guardarPacientes();
            bitacoralogCatalogo.insertar(usuario, 2004, "Catalogo", "Modificar Usuario");
            cout << "\nUsuario modificado exitosamente." << endl;
            Usuario::pausar();
            return;
        }
    }
    cout << "Usuario no encontrado." << endl;
    Usuario::pausar();
}

void Catalogo::desplegarPacientes() {
    Usuario::limpiarPantalla();
    cout << "Nombre: Jonathan Gonzalez" << endl; // Despliege de usuario
    cout << "Usuario: " << usuario << endl;
    cout << "\n=== LISTA DE Usuario ===" << endl;

    if (pacientes.empty()) {
        cout << "\nNo hay Usuario registrados." << endl;
        return;
    }

    // Encabezados con formato
    cout << left << setw(15) << "ID Usuario"
         << setw(20) << "NOMBRE"
         << setw(20) << "APELLIDO"
         << setw(15) << "CORREO"
         << setw(30) << "DIRECCION"
         << setw(15) << "TELEFONO" << endl;
    cout << string(115, '-') << endl;

    // Datos de pacientes
    for (const auto& p : pacientes) {
        cout << left << setw(15) << p.idPaciente
             << setw(20) << p.nombre
             << setw(20) << p.apellido
             << setw(15) << p.genero
             << setw(30) << p.direccion
             << setw(15) << p.telefono << endl;
    }
    bitacoralogCatalogo.insertar(usuario, 2005, "Catalogo", "Desplegar Usuario");
}
