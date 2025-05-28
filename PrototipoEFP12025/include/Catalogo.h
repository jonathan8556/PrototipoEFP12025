//Jonathan Samuel GOnzalez Ixpata
#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>
#include <vector>
#include "Bitacora.h"
#include <iomanip>

using namespace std;

class Catalogo {
private:
    struct Paciente {
        char idPaciente[20];
        char nombre[50];
        char apellido[50];
        char genero[15];
        char direccion[100];
        char telefono[15];
    };

    vector<Paciente> pacientes;
    string usuario;
    string archivo = "pacientes.dat";

    void cargarPacientes();
    void guardarPacientes();
    void ordenarPacientes();

public:
    void setUsuario(const string& u);
    void menuCatalogo();
    void crearPaciente();
    void borrarPaciente();
    void buscarPaciente();
    void modificarPaciente();
    void desplegarPacientes();
    void pausar();
};

#endif
