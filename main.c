#include<stdio.h>
#include<string.h>
#include "lista.h"
#include<assert.h>

#define N 10
#define true 1
#define false 0

/*  0  1  2  3  4  5  6  7  8  9   */
int g[N][N] = {
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, //0
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //1
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //2
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //3
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //4
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //5
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //6
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //8 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} //9 
};

int caminos[N];
int visitados[N];
int indice = 0;
int pesos[N] = {0, 120, 150, 10, 20, 60, 20, 30, 10, 0};
int duracion = 0;
int nuevaDuracion = 0;
TipoLista camino;
TipoLista caminoAux;

void caminoCritico(int origen, int destino);
void buscarCaminos(int origen, int destino);
void imprimirElementos();
void minimales(int minimal[N]);
void saltoLinea();
int esVacio(int minimal[N]);

int main() {

    TipoLista ordenada;
    TipoLista cola;
    cola = lista_vacia();
    ordenada = lista_vacia();
    int minimal[N];
    camino = lista_vacia();
    caminoAux = lista_vacia();

    /*asserts que chequea la correctitud de las variables inciales*/
    assert(g != NULL);
    assert(cola == NULL);
    assert(ordenada == NULL);
    assert(N == 10);
    assert(camino == NULL);
    assert(caminoAux == NULL);

    minimales(minimal);

    /*assert que chequea la salida de la funcion minimales*/
    assert(esVacio(minimal) == 1);

    for (int i = 0; i < N; i++) {
        if (minimal[i] == 0)
            cola = inserta_por_cola(cola, i);
    }

    if (es_lista_vacia(cola))
        printf("\nEl grafo es ciclico, no se puede realizar ordenamiento topologico\n");


    while (!es_lista_vacia(cola)) {
        int u = cola->info;
        ordenada = inserta_por_cola(ordenada, u);
        cola = borra_cabeza(cola);
        int v = -1;
        for (v = 0; v < N; v++) {
            if (g[u][v]) {
                minimal[v]--;
                if (minimal[v] == 0)
                    cola = inserta_por_cola(cola, v);
            }
        }
    }
    /*assert que chequea el resultado del ordenamiento topologico*/
    assert(ordenada != NULL);

    saltoLinea();
    printf("\nResultado de ordenamiento topologico\n");
    muestra_lista(ordenada);
    saltoLinea();
    printf("\n");
    memset(visitados, 0, sizeof (visitados));
    
    int org=0;
    int dest=9;
    
    /*assert que chequea que origen y destino*/
    assert(org != dest);
    assert(org >= 0);
    assert(dest >= 1);
    
    caminoCritico(org, dest);

    /*assert que chequea que nuevaDuracion*/
    assert(nuevaDuracion > 0);

    printf("El camino crítico de duracion %d es: ", nuevaDuracion);

    /*assert que chequea caminoAux*/
    assert(caminoAux != NULL);

    muestra_lista(caminoAux);
    saltoLinea();
    printf("\n");
    printf("Todos los caminos: \n");
    buscarCaminos(0, 9);
    saltoLinea();
    return 0;
}

void buscarCaminos(int origen, int destino) {
    
    /*asserts que chequean la entradas de la funcion*/
    assert(origen >= 0);
    assert(destino >= 1);

    visitados[origen] = true;
    caminos[indice] = origen;
    indice++;

    if (origen == destino) {
        imprimirElementos();
    } else {

        for (int k = 0; k < N; k++) {
            if (visitados[k] == false && g[origen][k])
                buscarCaminos(k, destino);
        }
    }

    visitados[origen] = false;
    indice--;
}

void caminoCritico(int origen, int destino) {

    /*asserts que chequean la entradas de la funcion*/
    assert(origen >= 0);
    assert(destino >= 1);
    

    visitados[origen] = true;
    caminos[indice] = origen;
    indice++;

    if (origen == destino) {
        for (int m = 0; m < indice; m++) {
            camino = inserta_por_cola(camino, caminos[m]);
            duracion = duracion + pesos[caminos[m]];
        }
        if (duracion > nuevaDuracion) {
            nuevaDuracion = duracion;
            caminoAux = camino;
            camino = lista_vacia();
            duracion = 0;
        }
    } else {
        int i;
        for (i = 0; i < N; i++) {
            if (visitados[i] == false && g[origen][i])
                caminoCritico(i, destino);
        }
    }

    visitados[origen] = false;
    indice--;

}

void imprimirElementos() {

    for (int j = 0; j < indice; j++)
        printf("[%d]->", caminos[j]);
    printf("\n");

}

void minimales(int minimal[N]) {
    int i = 0;
    int j = 0;
    for (i = 0; i < N; i++)
        minimal[i] = 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (g[i][j]) {
                minimal[j]++;
            }
        }
    }
}

void saltoLinea() {
    printf("\n#########################################################################################\n");
}

int esVacio(int minimal[N]) {
    for (int i = 0; i < N; i++) {
        if (minimal[i] != 0)
            return 1;
    }
}