#include "heap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_INICIAL 100
#define FACTOR_ENC 0.8
#define FACTOR_CRECIMIENTO 3
#define FACTOR_DECRECIMIENTO 0.25
#define PADRE(hijo) (size_t)((hijo - 1) / 2)
#define HIJO_IZQ(padre) (size_t)((padre * 2) + 1)
#define HIJO_DER(padre) (size_t)((padre * 2) + 2)

/* Dado dos elementos, se intercambian entre ellos.
 */
void swap(void * elemento_1, void * elemento_2);
void upheap(heap_t * heap, size_t i);
/* Dado un heap, se redimensiona el vector
 * de datos del heap. Devuelve true en caso
 * de éxito, false en caso contrario.
 * Pre: heap fue creado.
 * Post: la capacidad del heap será nueva_cantidad.
 */
bool heap_redimensionar(heap_t * heap, size_t nueva_capacidad);
void heapify(void ** datos,size_t n,cmp_func_t cmp);
void downheap(void** datos,size_t cantidad, size_t pos_inicial,cmp_func_t cmp);

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
	heap_t* heap = heap_crear(cmp);
	if(!heap) return NULL;
	
	heapify(arreglo, n, cmp);
	
	for(int i=0;i<n;i++) heap_encolar(heap,arreglo[i]);
	
	return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	heap_t * heap = heap_crear_arr(elementos, cant, cmp);

	for(size_t i = cant - 1; i >= 0; i--) 
		elementos[i] = heap_desencolar(heap);
	
	heap_destruir(heap, NULL);
}


bool heap_esta_vacio(const heap_t *heap) {
	return heap->cant == 0;	
}

size_t heap_cantidad(const heap_t *heap) {
	return heap->cant;
}

void *heap_ver_max(const heap_t *heap) {
	if(heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

bool heap_encolar(heap_t *heap, void *elem) {
	size_t cant = heap->cant;
	size_t tam = heap->tam;

	if(cant > (double) tam * FACTOR_ENC)
		if(!heap_redimensionar(heap, tam * FACTOR_CRECIMIENTO)) return false;

	heap->datos[cant] = elem;
	upheap(heap, cant);	
	
	heap->cant++;

	return true;
}

void *heap_desencolar(heap_t *heap) {
	if(heap_esta_vacio(heap))return NULL;
	
	void* maximo=heap->datos[0];
	
	swap(heap->datos[0],heap->datos[heap->cant-1]);
	
	heap->cant--;
	
	if((double) heap->cant < (double) heap->tam * FACTOR_DECRECIMIENTO) 
		heap_redimensionar(heap, heap->tam/2);

	downheap(heap->datos,heap->cant,0,heap->cmp);

	return maximo;
}
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	if(destruir_elemento){
		for(int i=0;i<heap->cant;i++) destruir_elemento(heap->datos[i]);		
	}
	
	free(heap->datos);
	free(heap);
}

/*****************************************************
 *                FUN. AUXILIARES
 *****************************************************/

void swap(void * elemento_1, void * elemento_2) {
	void * aux = elemento_1;
	elemento_1 = elemento_2;
	elemento_2 = aux;
}

void upheap(heap_t * heap, size_t i) {
	if(i <= 0) return;
	cmp_func_t cmp = heap->cmp;
	void ** datos = heap->datos;

	if(cmp(datos[i], datos[PADRE(i)]) > 0) {
		swap(datos[i], datos[PADRE(i)]);
		upheap(heap, PADRE(i));
	}
}

void downheap(void** datos,size_t cantidad, size_t pos_inicial,cmp_func_t cmp){
	if(pos_inicial >= cantidad) return;
	
	size_t pos_hijo_izq = HIJO_IZQ(pos_inicial);
	size_t pos_hijo_der = HIJO_DER(pos_inicial);
	
	if(pos_hijo_izq >= cantidad)return;
	
	if(cmp(datos[pos_inicial],datos[pos_hijo_izq])  > 0){
		swap(datos[pos_inicial], datos[pos_hijo_izq]);
		downheap(datos,cantidad,pos_hijo_izq, cmp);
	}
	
	if(pos_hijo_der >= cantidad)return;
	
	if(cmp(datos[pos_inicial],datos[pos_hijo_der]) > 0){
		swap(datos[pos_inicial], datos[pos_hijo_der]);
		downheap(datos,cantidad,pos_hijo_der, cmp);
	}	
}

bool heap_redimensionar(heap_t * heap, size_t nueva_capacidad) {
	void ** nuevo_arr = realloc(heap->datos, nueva_capacidad * sizeof(void *));
	if(!nuevo_arr) return false;
	heap->datos = nuevo_arr;
	heap->tam = nueva_capacidad;
	return true;
}
void _heapify(void ** datos,size_t n,size_t pos_inicial,cmp_func_t cmp){
	if(pos_inicial >= n) return;
	
	_heapify(datos,n,HIJO_IZQ(pos_inicial),cmp);
	
	_heapify(datos,n,HIJO_DER(pos_inicial),cmp);
	
	downheap(datos,n,pos_inicial,cmp);

}
	
void heapify(void ** datos,size_t n,cmp_func_t cmp){
	_heapify(datos,n,0,cmp);
}
