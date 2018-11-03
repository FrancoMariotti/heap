struct heap{
	void *datos;
	cmp_func_t cmp;
	size_t cantidad;
	size_t capacidad;
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
