#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANCIONES 10000

typedef struct {
    char id[50];
    char artists[200];
    char album_name[200];
    char track_name[200];
    float tempo;
    char track_genre[50];
} Cancion;

Cancion* canciones[MAX_CANCIONES];
int cantidad_canciones = 0;

void cargarCanciones(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo: %s\n", nombreArchivo);
        return;
    }

    char linea[1024];
    fgets(linea, sizeof(linea), archivo); // Saltar encabezado

    while (fgets(linea, sizeof(linea), archivo)) {
        Cancion* c = malloc(sizeof(Cancion));
        char* token;

        token = strtok(linea, ","); if (token) strcpy(c->id, token);
        token = strtok(NULL, ","); if (token) strcpy(c->artists, token);
        token = strtok(NULL, ","); if (token) strcpy(c->album_name, token);
        token = strtok(NULL, ","); if (token) strcpy(c->track_name, token);
        token = strtok(NULL, ","); if (token) c->tempo = atof(token);
        token = strtok(NULL, ",\n"); if (token) strcpy(c->track_genre, token);

        canciones[cantidad_canciones++] = c;

        if (cantidad_canciones >= MAX_CANCIONES) break;
    }

    fclose(archivo);
    printf("Se cargaron %d canciones.\n", cantidad_canciones);
}

void buscarPorGenero(const char* genero) {
    int encontrados = 0;
    for (int i = 0; i < cantidad_canciones; i++) {
        if (strcmp(canciones[i]->track_genre, genero) == 0) {
            printf("🎵 %s - %s [%s]\n", canciones[i]->artists, canciones[i]->track_name, canciones[i]->album_name);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron canciones del género '%s'.\n", genero);
    }
}

int main() {
    int opcion;
    char ruta[256], genero[50];

    do {
        printf("\n=== Spotifind ===\n");
        printf("1. Cargar canciones\n");
        printf("2. Buscar por género\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar salto de línea

        switch (opcion) {
            case 1:
                printf("Ingrese la ruta del archivo CSV: ");
                fgets(ruta, sizeof(ruta), stdin);
                ruta[strcspn(ruta, "\n")] = 0; // quitar salto de línea
                cargarCanciones(ruta);
                break;

            case 2:
                printf("Ingrese el género a buscar: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = 0;
                buscarPorGenero(genero);
                break;

            case 0:
                printf("¡Hasta luego!\n");
                break;

            default:
                printf("Opción no válida.\n");
        }

    } while (opcion != 0);

    for (int i = 0; i < cantidad_canciones; i++) {
        free(canciones[i]);
    }

    return 0;
}
