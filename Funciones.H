typedef struct
{
    int id;
    char marca[20];
    char modelo[20];
    int ano;
    float precio;
    char tipo[20];
    char estado[20];
    int disponible;
} Vehiculo;

typedef struct
{
    char nombreCliente[30];
    int edad;
    char marcaPreferida[20];
    float presupuesto;
} Cliente;

typedef struct
{
    int idVehiculo;
    char nombreCliente[30];
    float precioVenta;
} Venta;

void leerCadena(char *cadena, int n);
float validarFloatRango(float a, float b);
int menu();
void crearVehiculo(int pos);
void guardarVehiculo(Vehiculo *vehiculo, int pos);
int leerVehiculos(Vehiculo *vehiculos, int n);
void listarVehiculos();
int buscarVehiculo();
void editarVehiculo();
void buscarPorPreferencias();
void registrarVenta();