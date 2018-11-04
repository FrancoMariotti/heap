#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VOLUMEN 10000
#define CANT_HEAPS 100

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
/*
 * Prueba de creación de múltiples heaps.
 */
void prueba_heap_crear() {
    printf("INICIO DE PRUEBAS CON CREACION DE HEAP \n");
    
    heap_t* heap = heap_crear(NULL);
    print_test("Se creo heap", heap);
    print_test("Heap recien creado vacio", heap_esta_vacio(heap));
    print_test("Heap recien creado cantidad 0", heap_cantidad(heap) == 0);
    print_test("Heap recien creado ver máximo NULL", !heap_ver_max(heap));

    heap_destruir(heap, NULL);
    print_test("Destruyo el heap", true);
}
int _strcmp(const void * a, const void *b) {
    return strcmp((char *) a, (char *) b);
}
/*
 * Prueba de encolar y desencolar sobre un heap vacio.
 */
void prueba_heap_vacia() {
    printf("INICIO DE PRUEBAS CON heap VACIA\n");
    
    heap_t* heap = heap_crear(_strcmp);
    print_test("Creo heap vacio", heap);
    print_test("Desencolar heap vacio", heap_esta_vacio(heap) && heap_desencolar(heap) == NULL);

    // Apilo y desapilo un elemento.
    char * elemento = "A";
    
    print_test("Encolar un elemento en heap vacio", heap_encolar(heap, &elemento) && heap_ver_max(heap) == &elemento);
    print_test("Desencolo", heap_desencolar(heap) == &elemento);
    print_test("Desencolo", heap_desencolar(heap) == NULL);

    char *elemento1 = "A", *elemento2 = "B";
    print_test("Encolo un elemento", heap_encolar(heap, &elemento1) && heap_ver_max(heap) == &elemento1);
    print_test("Encolo otro elemento", heap_encolar(heap, &elemento2) && heap_ver_max(heap) == &elemento2);
    print_test("Desencolo elemento1", heap_desencolar(heap) == &elemento1);
    print_test("Desencolo elemento2", heap_desencolar(heap) == &elemento2);
    print_test("Desencolo heap vacio", heap_desencolar(heap) == NULL);
    print_test("Max heap vacio", heap_ver_max(heap) == NULL);

    heap_destruir(heap, NULL);
    print_test("Destruyo el heap", true);
}
/* Devuelve:
 *   menor a 0  si  a < b
 *       0      si  a == b
 *   mayor a 0  si  a > b
 * Donde: a y b son enteros.
 */
int numcmp(const void * a, const void *b) {
    return *(int *)b - *(int *)a;
}
/*
 * Pruebas sobre una heap con volumen de datos.
 * volumen va a ser la cantidad de datos que se van a usar.
 */
void prueba_heap_volumen(int volumen) {
    printf("INICIO DE PRUEBAS DE VOLUMEN (%d) \n", volumen);

    heap_t * heap = heap_crear(numcmp);
    int * elementos = malloc(volumen * sizeof(int));
    if(!elementos) return;
    
    bool ok = true;

    for(int i = 0; i < volumen; i++) {
        elementos[i] = i;
        ok &= heap_encolar(heap, &elementos[i]);
        ok &= heap_ver_max(heap) == &elementos[i];
        if(!ok) break;
    } 
    print_test("Se encolaron los elementos", ok);
    
    ok = true;
    for(int i = volumen - 1; i >= 0; i--) {
        ok &= heap_desencolar(heap) == &elementos[i];
        if(!ok) break;
    } 
    print_test("Se desencolaron los elementos", ok && heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("Destruyo el heap", true);
    free(elementos);
}
typedef struct nodo_prueba {
    int clave;
    void * dato;
}nodo_prueba_t;
/*
 * Función auxiliar. Destruye un heap vacío.
 * Pre: El heap fue creado y está vacio.
 * Post: El heap será destruido.
 */ 
void heap_vacio_destruir(void* heap){
    heap_destruir((heap_t*)heap, NULL);
}
int nodocmp(const void *a, const void *b) {
    nodo_prueba_t * a_c = (nodo_prueba_t *) a;
    nodo_prueba_t * b_c = (nodo_prueba_t *) b;
    return numcmp(&a_c->clave, &b_c->clave);
}
/*
 * Pruebo encolar elementos que deben ser 
 * destruidos manualmente cuando se destruye
 * el heap.
 */
void prueba_heap_destruir(){
    printf("INICIO DE PRUEBAS DE DESTRUIR\n");
    heap_t** heap = malloc(sizeof(heap_t*) * CANT_HEAPS);
    heap_t* heaps = heap_crear(nodocmp);
    bool ok = true;

    for(int i = 0; i < CANT_HEAPS; i++){
        heap[i] = heap_crear(NULL);
        ok &= heap_encolar(heaps, heap[i]);
    }
    print_test("Se encolaron los heaps", ok && !heap_esta_vacio(heaps));
    heap_destruir(heaps, heap_vacio_destruir);
    print_test("Se destruyo el heap y sus elementos", true);
    free(heap);
}

/*
 * Se ejecutan todas las pruebas de heap.
 */
void pruebas_heap_alumno() {
    prueba_heap_crear();
    prueba_heap_vacia();
    prueba_heap_volumen(VOLUMEN);
    prueba_heap_volumen(150000);
    prueba_heap_destruir();
}   
