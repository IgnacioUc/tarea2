#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para funciones de mayúsculas/minúsculas

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

// Función para comparación de strings sin importar mayúsculas/minúsculas
int compararStrings(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

void cargarCanciones(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo: %s\n", nombreArchivo);
        return;
    }

    char linea[1024];
    fgets(linea, sizeof(linea), archivo); // Saltar encabezado

    // Corrección aquí: paréntesis y llaves balanceadas
    while (fgets(linea, sizeof(linea), archivo) != NULL) {  // Se añade != NULL y se cierra correctamente
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
        if (compararStrings(canciones[i]->track_genre, genero)) {
            printf("🎵 %s - %s [%s]\n", 
                   canciones[i]->artists, 
                   canciones[i]->track_name, 
                   canciones[i]->album_name);
            encontrados++;
        }
    }
    printf("--> Se encontraron %d canciones del género '%s'.\n", encontrados, genero);
}

// Función para buscar por artista (NUEVA)
void buscarPorArtista(const char* artista) {
    int encontrados = 0;
    printf("\n🔍 Resultados para el artista '%s':\n", artista);
    for (int i = 0; i < cantidad_canciones; i++) {
        if (compararStrings(canciones[i]->artists, artista)) {
            printf("\n📌 Canción #%d\n", encontrados + 1);
            printf("   Artista: %s\n", canciones[i]->artists);
            printf("   Canción: %s\n", canciones[i]->track_name);
            printf("   Álbum: %s\n", canciones[i]->album_name);
            printf("   Género: %s\n", canciones[i]->track_genre);
            printf("   Tempo: %.2f BPM\n", canciones[i]->tempo);
            encontrados++;
        }
    }
    printf("\n--> Total: %d canciones encontradas.\n", encontrados);
}

int main() {
    int opcion;
    char ruta[256], genero[50], artista[100];  // 'artista' añadido

    do {
        printf("\n=== Spotifind ===\n");
        printf("1. Cargar canciones\n");
        printf("2. Buscar por género\n");
        printf("3. Buscar por artista\n");  // Opción nueva
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                printf("Ingrese la ruta del archivo CSV: ");
                fgets(ruta, sizeof(ruta), stdin);
                ruta[strcspn(ruta, "\n")] = 0;
                cargarCanciones(ruta);
                break;

            case 2:
                printf("Ingrese el género a buscar: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = 0;
                buscarPorGenero(genero);
                break;

            case 3:  // Nuevo caso para buscar por artista
                printf("Ingrese el nombre del artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = 0;
                buscarPorArtista(artista);
                break;

            case 0:
                printf("¡Hasta luego!\n");
                break;

            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 0);

    // Liberar memoria
    for (int i = 0; i < cantidad_canciones; i++) {
        free(canciones[i]);
    }

    return 0;
}
