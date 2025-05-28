//Jonathan Samuel GOnzalez Ixpata
#include "Bitacora.h"
#include "Usuario.h"
#include <iomanip>

void Bitacora::insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion) {
    ofstream archivo("bitacora.dat", ios::binary | ios::app);
    if (!archivo.is_open()) return;

    RegistroBitacora registro;
    strncpy(registro.usuario, usuario.c_str(), sizeof(registro.usuario));
    registro.codigo = codigo;
    strncpy(registro.aplicacion, aplicacion.c_str(), sizeof(registro.aplicacion));
    strncpy(registro.accion, accion.c_str(), sizeof(registro.accion));

    time_t now = time(nullptr);
    char* fecha = ctime(&now);
    fecha[strcspn(fecha, "\n")] = '\0';
    strncpy(registro.fechaHora, fecha, sizeof(registro.fechaHora));

    archivo.write(reinterpret_cast<char*>(&registro), sizeof(registro));
    archivo.close();
}

void Bitacora::mostrar() {
    ifstream archivo("bitacora.dat", ios::binary);
    if (!archivo.is_open()) return;

    RegistroBitacora registro;
    cout << "\n=== BITACORA ===" << endl;

    cout << left
         << setw(15) << "USUARIO"
         << setw(10) << "CODIGO"
         << setw(15) << "APP"
         << setw(20) << "ACCION"
         << setw(25) << "FECHA/HORA" << endl;
    cout << string(85, '-') << endl;

    while (archivo.read(reinterpret_cast<char*>(&registro), sizeof(registro))) {
        cout << left
             << setw(15) << registro.usuario
             << setw(10) << registro.codigo
             << setw(15) << registro.aplicacion
             << setw(20) << registro.accion
             << setw(25) << registro.fechaHora << endl;
    }
    archivo.close();
}

void Bitacora::menuBitacora() {
    int opcion;
    do {
        Usuario::limpiarPantalla();
        cout << "Nombre: Jonathan Samuel GOnzalez" << endl; // Reemplaza con tu nombre
        cout << "\n=== MENU BITACORA ===" << endl;
        cout << "1. Mostrar bitacora" << endl;
        cout << "2. Regresar" << endl;
        cout << "Seleccione: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                mostrar();
                Usuario::pausar();
                break;
            case 2:
                return;
            default:
                cout << "Opcion invalida." << endl;
                Usuario::pausar();
        }
    } while (true);
}
