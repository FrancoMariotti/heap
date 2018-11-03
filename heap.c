#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */


struct heap{
	void *datos;
	cmp_func_t heap_cmp;
	size_t cantidad;
	size_t tam;
};

bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad==0;	
}
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

void *heap_ver_max(const heap_t *heap){
	return heap->datos[0];
}

