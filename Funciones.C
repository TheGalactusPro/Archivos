#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerCadena(char *cadena, int n)
{
    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

float validarFloatRango(float a, float b)
{
    float n;
    int aux;
    do
    {
        aux = scanf("%f", &n);
        while (getchar() != '\n');
        if (aux != 1 || n < a || n > b)
        {
            printf("\nValor incorrecto.");
            printf("\n>> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

int menu()
{
    printf("\n===== CONCESIONARIA RUEDAS DE ORO =====");
    printf("\n1. Registrar vehiculo");
    printf("\n2. Listar vehiculos");
    printf("\n3. Editar vehiculo");
    printf("\n4. Buscar vehiculos por preferencias");
    printf("\n5. Registrar venta");
    printf("\n6. Salir");
    printf("\n>> ");
    return validarFloatRango(1, 6);
}

void crearVehiculo(int pos)
{
    Vehiculo vehiculo;
    printf("\nID: ");
    vehiculo.id = validarFloatRango(1, 9999);
    printf("\nMarca: ");
    leerCadena(vehiculo.marca, 20);
    printf("\nModelo: ");
    leerCadena(vehiculo.modelo, 20);
    printf("\nAño: ");
    vehiculo.ano = validarFloatRango(1990, 2026);
    printf("\nPrecio: ");
    vehiculo.precio = validarFloatRango(1000, 100000);
    printf("\nTipo (Camioneta/SUV/Sedan): ");
    leerCadena(vehiculo.tipo, 20);
    printf("\nEstado (Nuevo/Usado): ");
    leerCadena(vehiculo.estado, 20);
    vehiculo.disponible = 1;
    guardarVehiculo(&vehiculo, pos);
}

void guardarVehiculo(Vehiculo *vehiculo, int pos)
{
    FILE *f;
    if (pos == -1)
        f = fopen("vehiculos.dat", "ab+");
    else
        f = fopen("vehiculos.dat", "rb+");
    if (f == NULL)
        return;
    if (pos != -1)
        fseek(f, pos, SEEK_SET);
    fwrite(vehiculo, sizeof(Vehiculo), 1, f);
    fclose(f);
}

int leerVehiculos(Vehiculo *vehiculos, int n)
{
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL)
        return 0;
    int cantidad = fread(vehiculos, sizeof(Vehiculo), n, f);
    fclose(f);
    return cantidad;
}

void listarVehiculos()
{
    Vehiculo vehiculos[100];
    int cantidad = leerVehiculos(vehiculos, 100);
    printf("\nID\tMarca\tModelo\tPrecio\tDisponible\n");
    for (int i = 0; i < cantidad; i++)
    {
        printf("%d\t%s\t%s\t%.2f\t%s\n", vehiculos[i].id, vehiculos[i].marca, vehiculos[i].modelo, vehiculos[i].precio, vehiculos[i].disponible ? "SI" : "NO");
    }
}

int buscarVehiculo()
{
    int idBuscar;
    Vehiculo vehiculo;
    int pos = 0;
    int encontrado = 0;
    printf("\nIngrese ID del vehiculo: ");
    idBuscar = validarFloatRango(1, 9999);
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL)
        return -1;
    while (fread(&vehiculo, sizeof(Vehiculo), 1, f))
    {
        if (vehiculo.id == idBuscar)
        {
            encontrado = 1;
            break;
        }
        pos = ftell(f);
    }
    fclose(f);
    if (!encontrado)
        return -1;
    return pos;
}

void editarVehiculo()
{
    int pos = buscarVehiculo();
    if (pos == -1)
    {
        printf("\nVehiculo no encontrado.");
        return;
    }
    crearVehiculo(pos);
}

void buscarPorPreferencias()
{
    char marca[20];
    float presupuesto;
    Vehiculo vehiculo;
    printf("\nMarca deseada: ");
    leerCadena(marca, 20);
    printf("\nPresupuesto maximo: ");
    presupuesto = validarFloatRango(1000, 100000);
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL)
    {
        printf("\nNo existen vehiculos registrados.");
        return;
    }
    printf("\nVehiculos encontrados:");
    while (fread(&vehiculo, sizeof(Vehiculo), 1, f))
    {
        if (strcmp(vehiculo.marca, marca) == 0 && vehiculo.precio <= presupuesto && vehiculo.disponible == 1)
        {
            printf("\nID:%d | %s %s | %.2f", vehiculo.id, vehiculo.marca, vehiculo.modelo, vehiculo.precio);
        }
    }
    fclose(f);
}
void registrarVenta()
{
    Venta venta;
    Vehiculo vehiculo;
    Vehiculo vehiculos[100];
    int n = 0;
    int encontrado = 0;
    printf("\nID Vehiculo: ");
    venta.idVehiculo = validarFloatRango(1, 9999);
    printf("\nNombre Cliente: ");
    leerCadena(venta.nombreCliente, 30);
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL)
        return;
    while (fread(&vehiculo, sizeof(Vehiculo), 1, f))
    {
        if (vehiculo.id == venta.idVehiculo && vehiculo.disponible == 1)
        {
            vehiculo.disponible = 0;
            venta.precioVenta = vehiculo.precio;
            encontrado = 1;
        }
        vehiculos[n++] = vehiculo;
    }
    fclose(f);
    if (!encontrado)
    {
        printf("\nVehiculo no disponible.");
        return;
    }
    f = fopen("vehiculos.dat", "wb");
    for (int i = 0; i < n; i++)
    {
        fwrite(&vehiculos[i], sizeof(Vehiculo), 1, f);
    }
    fclose(f);
    FILE *fv = fopen("ventas.dat", "ab");
    fwrite(&venta, sizeof(Venta), 1, fv);
    fclose(fv);
    printf("\nVenta registrada correctamente.");
}