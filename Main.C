#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    int opc, opc2;
    do
    {
        opc = menu();
        switch (opc)
        {
        case 1:
            crearVehiculo(-1);
            break;
        case 2:
            listarVehiculos();
            break;
        case 3:
            editarVehiculo();
            break;
        case 4:
            buscarPorPreferencias();
            break;
        case 5:
            registrarVenta();
            break;
        case 6:
            printf("\nGracias por utilizar el sistema.");
            break;
        default:
            printf("\nOpcion no valida.");
        }
        printf("\nSi desea continuar: 1 (Si) o 2 (No)");
        printf("\n>> ");
        opc2=validarFloatRango(1,2);
    } while (opc2 == 1);
    return 0;
}