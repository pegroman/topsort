#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

TipoLista lista_vacia(void) {
    return NULL;
}

int es_lista_vacia(TipoLista lista) {
    return lista == NULL;
}

TipoLista inserta_por_cabeza(TipoLista lista, int valor) {
    struct Nodo * nuevo = malloc(sizeof (struct Nodo));
    nuevo->info = valor;
    nuevo->sig = lista;
    lista = nuevo;
    return lista;
}

TipoLista inserta_por_cola(TipoLista lista, int valor) {
    struct Nodo * aux, * nuevo;

    nuevo = malloc(sizeof (struct Nodo));
    nuevo->info = valor;
    nuevo->sig = NULL;
    if (lista == NULL)lista = nuevo;
    else {
        for (aux = lista; aux ->sig != NULL; aux = aux ->sig);
        aux ->sig = nuevo;
    }
    return lista;
}

TipoLista borra_cabeza(TipoLista lista) {
    struct Nodo * aux;

    if (lista != NULL) {
        aux = lista->sig;
        free(lista);
        lista = aux;
    }
    return lista;
}

TipoLista borra_cola(TipoLista lista) {
    struct Nodo * aux, * atras;

    if (lista != NULL) {
        for (atras = NULL, aux = lista; aux ->sig != NULL; atras = aux, aux = aux ->sig);
        free(aux);
        if (atras == NULL)lista = NULL;
        else atras->sig = NULL;
    }
    return lista;
}

int longitud_lista(TipoLista lista) {
    struct Nodo * aux;
    int contador = 0;
    for (aux = lista; aux != NULL; aux = aux ->sig) contador++;
    return contador;
}

TipoLista libera_lista(TipoLista lista) {
    struct Nodo *aux, *otroaux;

    aux = lista;
    while (aux != NULL) {
        otroaux = aux ->sig;
        free(aux);
        aux = otroaux;
    }
    return NULL;
}

int pertenece(TipoLista lista, int valor) {
    struct Nodo * aux;

    for (aux = lista; aux != NULL; aux = aux ->sig)
        if (aux ->info == valor) return 1;
    return 0;

}

void muestra_lista(TipoLista lista) {
    struct Nodo * aux;

    printf("->");
    for (aux = lista; aux != NULL; aux = aux ->sig)
        printf("[%d]->", aux ->info);
    printf("|\n");

}

