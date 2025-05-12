#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Función para comparar strings sin distinguir mayúsculas/minúsculas
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
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char linea[1024];
    fgets(linea, sizeof(linea), archivo); // Saltar encabezado

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
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
    printf("✓ Se cargaron %d canciones.\n", cantidad_canciones);
}

void buscarPorGenero(const char* genero) {
    int encontrados = 0;
    printf("\n🔍 Resultados para género '%s':\n", genero);
    for (int i = 0; i < cantidad_canciones; i++) {
        if (compararStrings(canciones[i]->track_genre, genero)) {
            printf("\n🎵 Canción #%d", encontrados + 1);
            printf("\n   Artista: %s", canciones[i]->artists);
            printf("\n   Álbum: %s", canciones[i]->album_name);
            printf("\n   Tempo: %.2f BPM\n", canciones[i]->tempo);
            encontrados++;
        }
    }
    printf("\n✅ Total: %d canciones.\n", encontrados);
}

void buscarPorArtista(const char* artista) {
    int encontrados = 0;
    printf("\n🔍 Resultados para artista '%s':\n", artista);
    for (int i = 0; i < cantidad_canciones; i++) {
        if (compararStrings(canciones[i]->artists, artista)) {
            printf("\n🎵 Canción #%d", encontrados + 1);
            printf("\n   Nombre: %s", canciones[i]->track_name);
            printf("\n   Álbum: %s", canciones[i]->album_name);
            printf("\n   Género: %s", canciones[i]->track_genre);
            printf("\n   Tempo: %.2f BPM\n", canciones[i]->tempo);
            encontrados++;
        }
    }
    printf("\n✅ Total: %d canciones.\n", encontrados);
}

void buscarPorTempo() {
    int opcion;
    printf("\n🎶 Buscar por tempo:");
    printf("\n1. Lentas (<80 BPM)");
    printf("\n2. Moderadas (80-120 BPM)");
    printf("\n3. Rápidas (>120 BPM)");
    printf("\nSeleccione una opción: ");
    scanf("%d", &opcion);
    getchar();

    float min = 0, max = 0;
    const char* tipo = "";

    switch (opcion) {
        case 1: min = 0;   max = 80;  tipo = "Lentas"; break;
        case 2: min = 80;  max = 120; tipo = "Moderadas"; break;
        case 3: min = 120; max = 999; tipo = "Rápidas"; break;
        default: printf("❌ Opción inválida.\n"); return;
    }

    int encontrados = 0;
    printf("\n🔍 Canciones %s (%.0f-%.0f BPM):\n", tipo, min, max);
    for (int i = 0; i < cantidad_canciones; i++) {
        if (canciones[i]->tempo >= min && canciones[i]->tempo <= max) {
            printf("\n🎵 Canción #%d", encontrados + 1);
            printf("\n   Artista: %s", canciones[i]->artists);
            printf("\n   Nombre: %s", canciones[i]->track_name);
            printf("\n   Tempo: %.2f BPM\n", canciones[i]->tempo);
            encontrados++;
        }
    }
    printf("\n✅ Total: %d canciones %s.\n", encontrados, tipo);
}

int main() {
    int opcion;
    char input[256];

    printf("===== 🎧 Spotifind =====\n");
    do {
        printf("\nMenú principal:");
        printf("\n1. Cargar canciones");
        printf("\n2. Buscar por género");
        printf("\n3. Buscar por artista");
        printf("\n4. Buscar por tempo");
        printf("\n0. Salir");
        printf("\nSeleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("\nIngrese la ruta del archivo CSV: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                cargarCanciones(input);
                break;
            case 2:
                printf("\nIngrese el género a buscar: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                buscarPorGenero(input);
                break;
            case 3:
                printf("\nIngrese el artista a buscar: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                buscarPorArtista(input);
                break;
            case 4:
                buscarPorTempo();
                break;
            case 0:
                printf("\n🎶 ¡Hasta pronto!\n");
                break;
            default:
                printf("\n❌ Opción inválida.\n");
        }
    } while (opcion != 0);

    // Liberar memoria
    for (int i = 0; i < cantidad_canciones; i++) {
        free(canciones[i]);
    }

    return 0;
}
