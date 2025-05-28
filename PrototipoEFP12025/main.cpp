//Jonathan Samuel GOnzalez Ixpata
#include <iostream>
#include "Usuario.h"
#include "Catalogo.h"
#include "Bitacora.h"

using namespace std;

void menuPrincipal(const string& usuario) {
    Catalogo catalogo;
    catalogo.setUsuario(usuario);
    Bitacora bitacora;

    int opcion;
    do {
        Usuario::limpiarPantalla();
        cout << "Nombre: Jonathan Gonzalez" << endl;
        cout << "\n=== MENU PRINCIPAL ===" << endl; //menu princial
        cout << "Usuario: " << usuario << endl;
        cout << "1. Catalogos" << endl;
        cout << "2. Informes" << endl; //Reportes del sistema
        cout << "3. Seguridad" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                catalogo.menuCatalogo();
                break;
            case 2:
                catalogo.desplegarPacientes();
                Usuario::pausar();
                break;
            case 3:
                bitacora.mostrar();
                bitacora.menuBitacora();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                return;
            default:
                cout << "Opcion invalida." << endl;
                Usuario::pausar();
        }
    } while (true);
}

int main() {
    Usuario usuario;
    string usuarioAutenticado;
    if (usuario.menuAutenticacion(usuarioAutenticado)) {
        menuPrincipal(usuarioAutenticado);
    }
    return 0;
}
