#include "heap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_INICIAL 100
#define PADRE(hijo) (size_t)((hijo - 1) / 2)
#define HIJO_IZQ(padre) (size_t)((padre * 2) + 1)
#define HIJO_DER(padre) (size_t)((padre * 2) + 2)

void swap(void * datos[], size_t i, size_t j);
void upheap(heap_t * heap, size_t i);

struct heap{
	void ** datos;
	cmp_func_t cmp;
	size_t cant;
	size_t tam;
};

/*****************************************************
 *                PRIMITIVAS HEAP
 *****************************************************/

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t * heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	
	void ** datos = malloc(sizeof(void *) * TAM_INICIAL);
	if(!datos){
		free(heap);
		return NULL;
	}
	heap->datos = datos;
	heap->cmp = cmp;
	heap->cant = 0;
	heap->tam = TAM_INICIAL;

	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	
	heap_t* heap=heap_crear(cmp);
	
	if(!heap)return NULL;
	
	for(int i=0;i<n;i++) heap_encolar(heap,arreglo[i]);
	
	return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	
}


bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;	
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

bool heap_encolar(heap_t *heap, void *elem) {

}

void *heap_desencolar(heap_t *heap) {
	if(heap_esta_vacio(heap))return NULL;
	
	void* maximo=heap->datos[0];
	
	swap(heap->datos[0],heap->datos[heap->cant-1]);
	
	heap->cantidad--;
	
	
			heap_redimensionar(heap, heap->tam / 2);

	
	return maximo;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	if(destruir_elemento){
		for(int i=0;i<heap->cantidad;i++) destruir_elemento(heap->datos[i]);		
	}
	
	free(heap->datos);
	free(heap);
}

void pruebas_heap_alumno(void) {

}

/*****************************************************
 *                FUN. AUXILIARES
 *****************************************************/

void swap(void * dato1,void* dato2) {
	void * aux = datos1;
	dato1 = dato2;
	datos2 = aux;
}

void upheap(heap_t * heap, size_t i) {
	if(i <= 0) return;
	cmp_func_t cmp = heap->cmp;
	size_t cant = heap->cant;
	void ** datos = heap->datos;

	if(cmp(datos[i], datos[PADRE(i)]) > 0) {
		swap(datos, i, PADRE(i));
		upheap(heap, PADRE(i));
	}
}
void downheap(heap_t * 
