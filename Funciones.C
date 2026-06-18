#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu()
{
    printf("Seleccione una opcion\n");
    printf("1.Crear estudiante\n");
    printf("2.Listar estudiantes\n");
    printf("3.Editar estudiantes\n");
    printf(">> ");
    int opc = validarFloatRango(1, 3);
    return opc;
}

void crearEstudiante(int pos)
{
    Estudiante estudiante;
    printf("Ingrese el nombre del estudiante: ");
    leerCadena(estudiante.nombre, 20);
    printf("Ingrese la edad del estudiante: ");
    estudiante.edad = validarFloatRango(1, 50);
    printf("Ingrese el numero de calificaciones: ");
    estudiante.numCalificaciones = validarFloatRango(1, 10);
    for (int i = 0; i < estudiante.numCalificaciones; i++)
    {
        printf("Ingrese el nombre de la materia: ");
        leerCadena(estudiante.calificaciones[i].nombreMateria, 20);
        printf("Ingrese las calificaciones: \n");
        int prom = 0;
        for (int j = 0; j < 3; j++)
        {
            printf("Nota %d: ", j + 1);
            estudiante.calificaciones[i].notas[j] = validarFloatRango(1, 10);
            prom += estudiante.calificaciones[i].notas[j];
        }
        estudiante.calificaciones[i].promedio = prom / 3;
    }
    guardarEstudiante(&estudiante, pos);
}

void guardarEstudiante(Estudiante *estudiante, int pos)
{
    FILE *f;
    if (pos != -1)
    {
        f = fopen("calificaciones.dat", "rb+");
    }
    else
    {
        f = fopen("calificaciones.dat", "ab+");
    }
    if (f == NULL)
    {
        return;
    }
    if (pos != -1)
    {
        fseek(f, pos, SEEK_SET);
    }
    fwrite(estudiante, sizeof(Estudiante), 1, f);
    fclose(f);
}

int leerEstudiante(Estudiante *estudiantes, int n)
{
    FILE *f = fopen("calificaciones.dat", "rb+");
    if (f == NULL)
    {
        return 0;
    }
    int numEstudiantes = fread(estudiantes, sizeof(Estudiante), n, f);
    fclose(f);
    return numEstudiantes;
}

int buscarEstudiante()
{
    char nombreBuscar[20];
    Estudiante estudiante;
    int pos = 0;
    int flag = 0;
    printf("Ingrese el nombre del estudiante a buscar: ");
    leerCadena(nombreBuscar, 20);
    FILE *f = fopen("calificaciones.dat", "rb+");
    if (f == NULL)
    {
        return -1;
    }
    while (fread(&estudiante, sizeof(Estudiante), 1, f))
    {
        if (strcmp(estudiante.nombre, nombreBuscar) == 0)
        {
            flag = 1;
            break;
        }
        pos = ftell(f);
    }
    fclose(f);
    if (flag == 0)
    {
        pos = -1;
    }
    return pos;
}

void editarEstudiante()
{
    int pos = buscarEstudiante();
    crearEstudiante(pos);
}

void imprimirEstudiante()
{
    Estudiante estudiantes[10];
    int numEstudiantes = leerEstudiante(estudiantes, 10);
    printf("#\t\tNombre\t\tEdad\t\tCant.Mat.\n");
    for (int i = 0; i < numEstudiantes; i++)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\n", i, estudiantes[i].nombre, estudiantes[i].edad, estudiantes[i].numCalificaciones);
    }
}

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
        while ((getchar()) != '\n');
        if (aux != 1 || n < a || n > b)
        {
            printf("Error: El valor ingresado es incorrecto\n");
            printf(">> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

void eliminarEstudiante()
{
    int pos = buscarEstudiante();
    if (pos != -1)
    {
        FILE *f = fopen("calificaciones.dat", "rb+");
        if (f == NULL)
        {
            return;
        }
        fseek(f, pos, SEEK_SET);
        Estudiante estudiante;
        while (fread(&estudiante, sizeof(Estudiante), 1, f))
        {
            fseek(f, -sizeof(Estudiante), SEEK_CUR);
            Estudiante estudianteVacio = {"", 0, 0, {{0}}};
            fwrite(&estudianteVacio, sizeof(Estudiante), 1, f);
            break;
        }
        fclose(f);
    }
}