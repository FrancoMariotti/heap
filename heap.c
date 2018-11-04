#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */

struct heap{
	void *datos;
	cmp_func_t heap_cmp;
	size_t cant;
	size_t tam;
};

heap_t *heap_crear(cmp_func_t cmp) {
	
}


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	
	heap_t* heap=heap_crear(cmp);
	
	for(int i=0;i<n;i++) heap->datos[i]=arreglo[i];
	
	return heap;
}
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {

}


bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad==0;	
}
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}


void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {

}


bool heap_encolar(heap_t *heap, void *elem) {

}

void *heap_desencolar(heap_t *heap) {

}


void pruebas_heap_alumno(void) {

}
