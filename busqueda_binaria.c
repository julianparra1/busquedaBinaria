#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define BUSQUEDA "zinsang"

void imprimir_array(char *array[], size_t arr_size);
int busquedaBinaria(char *arregloCadenas[], int izquierda, int derecha, char buscar[]);
int busquedaPobre(char *array[], size_t arr_size, char cadena[]);
int cmpfunc(const void * a, const void * b);
size_t tokenizar(char *cadena, char **arr, long fsize);


// Función de búsqueda binaria en un arreglo de cadenas
int busquedaBinaria(char *arregloCadenas[], int izquierda, int derecha, char buscar[]) {
    int contador = 0;
    while (izquierda <= derecha) {
        contador++;

        // Calcula el índice medio del rango actual
        int medio = izquierda + (derecha - izquierda) / 2;

        // Compara la cadena en la posición media con la cadena buscada
        if (strcmp(arregloCadenas[medio], buscar) == 0) {
            return contador;
        }

        // Ajusta los límites del rango según la comparación de cadenas
        if (strcmp(arregloCadenas[medio], buscar) < 0) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    // Si la cadena no se encuentra, devuelve -1
    return -1;
}

int main(int argc, char const *argv[]) {
    // Declaración e inicialización de variables
    FILE *f = fopen("words.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *cadena = malloc(fsize + 1);
    char **arregloCadenas = malloc((fsize + 1) * sizeof(char*));
    size_t bytesRead = fread(cadena, 1, fsize, f);
    fclose(f);
    cadena[fsize] = 0;
    char buscar[255] = {0};

    size_t tokenCount;
    

    // Tokenización y llenado del arreglo de cadenas
    tokenCount = tokenizar(cadena, arregloCadenas, fsize);

    // Ordenamiento del arreglo de cadenas
    qsort(arregloCadenas, tokenCount, sizeof(arregloCadenas[0]), cmpfunc);
    
    printf("Ingrese la cadena a buscar:\n");
    fgets(buscar, 255, stdin);
    buscar[strcspn(buscar, "\r\n")] = '\0';
    for(int i = 0; buscar[i]; i++){
        buscar[i] = tolower(buscar[i]);
    }

    // Impresión del arreglo ordenado
    //imprimir_array(arregloCadenas, tokenCount);

    // Búsqueda Eficiente (Binaria)
    printf("-== Búsqueda Eficiente (Binaria) ==-\n");
    clock_t inicio_binario = clock();
    int contador_binario = busquedaBinaria(arregloCadenas, 0, tokenCount - 1, buscar);
    clock_t final_binario = clock();
    float tiempo_binario = (float)(final_binario - inicio_binario) / CLOCKS_PER_SEC;

    // Impresión de resultados de la búsqueda eficiente
    if (contador_binario == -1) {
        printf("No se encontró el elemento en el arreglo.\n");
    } else {
        printf("El elemento \"%s\" está en el arreglo. Se encontró en \033[4m%d\033[24m intentos.\n", buscar, contador_binario);
    }
    printf("Tiempo de búsqueda binaria: %f segundos.\n\n", tiempo_binario);

    // Búsqueda Ineficiente
    printf("-== Búsqueda Ineficiente ==-\n");
    clock_t inicio_pobre = clock();
    int contador_pobre = busquedaPobre(arregloCadenas, tokenCount, buscar);
    clock_t fin_pobre = clock();
    float tiempo_pobre = (float)(fin_pobre - inicio_pobre) / CLOCKS_PER_SEC;

    // Impresión de resultados de la búsqueda ineficiente
    if (contador_pobre == -1) {
        printf("No se encontró el elemento en el arreglo.\n");
    } else {
        printf("El elemento \"%s\" está en el arreglo. Se encontró en \033[4m%d\033[24m intentos.\n", buscar, contador_pobre);
    }
    printf("Tiempo de búsqueda \"pobre\": %f segundos.\n\n", tiempo_pobre);

    // Liberación de memoria
    free(cadena);
    for (size_t i = 0; i < tokenCount; i++) {
        free(arregloCadenas[i]);
    }
    free(arregloCadenas);

    return 0;
}


// Función para tokenizar una cadena y llenar un arreglo de cadenas
size_t tokenizar(char *cadena, char **arr, long fsize) {
    // Inicialización de variables
    size_t tokenCount = 0;  // Contador de tokens (palabras)
    char *token = strtok(cadena, " \n");  // Obtener el primer token (palabra)

    // Iterar mientras haya tokens y no se haya alcanzado el tamaño máximo
    while (token != NULL && tokenCount < fsize) {
        // Eliminar caracteres de nueva línea (si existen) al final del token
        token[strcspn(token, "\r\n")] = '\0';

        // Asignar memoria para el token en el arreglo y copiar el token
        arr[tokenCount] = malloc(strlen(token) + 1);
        
        // minusculas!
        for(int i = 0; token[i]; i++){
            token[i] = tolower(token[i]);
        }

        strcpy(arr[tokenCount], token);

        // Incrementar el contador de tokens
        tokenCount++;

        // Obtener el próximo token
        token = strtok(NULL, " \r\n");
    }

    // Devolver la cantidad total de tokens encontrados
    return tokenCount;
}


void imprimir_array(char *array[], size_t arr_size) {
    printf("[");
    for (size_t i = 0; i < arr_size; i++) {
        printf("%s%s", array[i], (i == arr_size - 1) ? "" : ",");
    }
    printf("]\n");
}

// Función de búsqueda ineficiente en un arreglo de cadenas
int busquedaPobre(char *array[], size_t arr_size, char cadena[]) {
    for (size_t i = 0; i < arr_size && arr_size != 0; i++) {
        // Compara la cadena actual con la cadena buscada
        if (strcmp(cadena, array[i]) == 0) {
            // Si se encuentra la cadena, devuelve la posición (1-indexed)
            return i + 1;
        }
    }

    // Si la cadena no se encuentra, devuelve -1
    return -1;
}

int cmpfunc(const void * a, const void * b) {
   return (strcmp(*(char **)a, *(char **)b));
}