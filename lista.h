struct Nodo {
    int info;
    struct Nodo * sig;
};

typedef struct Nodo *TipoLista;

extern TipoLista lista_vacia(void);
extern int es_lista_vacia(TipoLista lista);
extern TipoLista inserta_por_cabeza(TipoLista lista, int valor );
extern TipoLista inserta_por_cola(TipoLista lista, int valor );
extern TipoLista borra_cabeza(TipoLista lista);
extern TipoLista borra_cola(TipoLista lista);
extern int longitud_lista(TipoLista lista);
extern void muestra_lista(TipoLista lista);
extern int pertenece(TipoLista lista, int valor );
extern TipoLista libera_lista(TipoLista lista);
