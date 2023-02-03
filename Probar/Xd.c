#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_HISTORIAL 100

struct historial {
    char nombre_paciente[100];
    char edad_paciente[100];
    char genero_paciente[100];
    char informacion_contacto[100];
    char fecha_hora[20];
};

int contador_historial = 0;
struct historial historial[MAX_HISTORIAL];

void ingresar_paciente() {
    if (contador_historial == MAX_HISTORIAL) {
        printf("Lo siento, no se pueden ingresar más pacientes en este momento. Por favor intente mas tarde.\n");
        return;
    }

    printf("Ingrese el nombre del paciente: ");
    scanf("%s", historial[contador_historial].nombre_paciente);

    printf("Ingrese la edad del paciente: ");
    scanf("%s", historial[contador_historial].edad_paciente);

    printf("Ingrese genero del paciente: ");
    scanf("%s", historial[contador_historial].genero_paciente);

    printf("Ingrese la informacion de contacto del paciente (teléfono o correo electronico): ");
    scanf("%s", historial[contador_historial].informacion_contacto);


    struct tm fecha;
    printf("Ingrese la fecha de nacimiento del paciente (formato: dd/mm/yyyy): ");
    scanf("%d/%d/%d", &fecha.tm_mday, &fecha.tm_mon, &fecha.tm_year);
    fecha.tm_mon--;
    fecha.tm_year -= 1900;
    strftime(historial[contador_historial].fecha_hora, sizeof(historial[contador_historial].fecha_hora), "%d/%m/%Y", &fecha);
    
    int i;
    for(i=0;i<contador_historial;i++) {
        if(strcmp(historial[i].fecha_hora, historial[contador_historial].fecha_hora) == 0) {
            printf("Ya existe una cita para esa fecha, por favor seleccione otra fecha");
            return;
        }
    }


    printf("Historial aguardado exitosamente.\n", historial[contador_historial].nombre_paciente);
    contador_historial++;
}


void ver_historial() {
    int i;
    if (contador_historial == 0) {
        printf("No hay historial almacenado.\n");
    } else {
        printf("Historial Guardado:\n");
        for (i = 0; i < contador_historial; i++) {
            printf("\n-Paciente: %s, \n Contacto: %s, \n Fecha: %s\n", historial[i].nombre_paciente, historial[i].informacion_contacto, historial[i].fecha_hora);
        }
    }
}

// Funcion exportar citas en proceso....


void guardar_historial() {
    FILE *archivo;
    archivo = fopen("historial.txt", "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }

    int i;
    for (i = 0; i < contador_historial; i++) {
        fprintf(archivo, "Nombre del Paciente: %s, Edad: %s, Género: %s, Contacto: %s, Fecha: %s\n", historial[i].nombre_paciente, historial[i].edad_paciente, historial[i].genero_paciente, historial[i].informacion_contacto, historial[i].fecha_hora);
    }

    fclose(archivo);
    printf("Historial Almacenado exitosamente al archivo historial.txt.\n");
}

int main() {
    while (1) {
        printf("~~~~~~~~Menu de opciones~~~~~~~\n");
        printf("1. Ingresar datos del paciente\n");
        printf("2. Ver historial\n");
        printf("3. Guardar historial\n");
        printf("4. Salir\n");

        int opcion;
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresar_paciente();
                break;

            case 2:
                ver_historial();
                break;
            case 3:
                guardar_historial();
                break;
            case 4:
                return 0;
            default:
                printf("Opcion invalida. Por favor seleccione una opcion valida del menu.\n");
                break;
        }
    }
}
