# tarea2# 🎧 Spotifind

Spotifind es una aplicación en lenguaje C que permite cargar canciones desde un archivo CSV y realizar búsquedas por género, artista o tempo. Está diseñada para ejecutarse en consola con una interfaz sencilla y funcional.

## 📦 Requisitos

- Compilador de C (como `gcc`)
- Un archivo CSV con canciones que tenga el siguiente formato:



## 🔍 Búsquedas disponibles
Por género: busca canciones que coincidan con el género ingresado (sin distinguir mayúsculas o minúsculas).

Por artista: busca canciones del artista ingresado exactamente.

Por tempo:

Lentas: menos de 80 BPM

Moderadas: entre 80 y 120 BPM

Rápidas: más de 120 BPM

## ✅ Características
Hasta 10.000 canciones cargadas en memoria.

Comparación insensible a mayúsculas/minúsculas.

Liberación automática de memoria al finalizar.

⚠️ Limitaciones
No se procesan correctamente los campos entre comillas que contengan comas (ejemplo: "Beyoncé, Jay-Z").

La búsqueda por artista es exacta (no parcial).

No se valida si la entrada del usuario contiene caracteres no válidos.

## 👥 Participantes
Ignacio Calderón


## ⚙️ Compilación

Puedes compilar el programa usando:

```bash
gcc -o spotifind spotifind.c

## ejecucion

./spotifind

Aparecerá un menú con las siguientes opciones:

Cargar canciones: pide la ruta del archivo CSV y carga los datos.

Buscar por género: muestra las canciones que pertenecen a un género específico.

Buscar por artista: busca canciones según el artista indicado.

Buscar por tempo: filtra canciones por su velocidad (BPM).

Salir: termina el programa.


