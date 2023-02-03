#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <time.h>
#include<stdbool.h>

#define TAMNOMBRE 10
#define RESET_COLOR    "\x1b[0m"
#define AMARILLO_T "\x1b[33m"
#define ROJO_T     "\x1b[31m"
#define CYAN_T     "\x1b[36m"
#define VERDE_T        "\x1b[32m"

typedef struct
{
    char nombre[TAMNOMBRE];
    char color[10];
    float precio;
    int cantidadinv;
    
}Fruta;

void InicioOperacion(int, char**);
Fruta* RegistrarFruta(int pos, Fruta *Arreglo);
void EliminarFruta(Fruta*lista, int canidad);
Fruta* Llenarlista(Fruta *Lista, int cantidad);
Fruta *ComprarFruta(Fruta* Lista, int cantidad);
void Actualizartxt(Fruta *Lista, int cantidad);
Fruta* ActualizaTDA(Fruta *lista, int pos);
Fruta* OrdenarPrecio(Fruta* lista, int cantidad);
void Crearcopia(Fruta * lista, int cantidad);
void OrdenarNombre(Fruta* lista, int cantidad);
char ConvertirLetra(char minuscula);
void Imprimir(Fruta* lista, int tam);
void GenerarIndices(int *arregloindices);
void BuscarFruta( Fruta *lista, int tam);
void Generartxtindices();
