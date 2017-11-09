#include "heap.h"
#include "testing.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CANT 1000

bool prueba_heapsort(size_t elementos, cmp_func_t cmp){
	int* vd  = calloc(elementos, sizeof(int));
	if (vd == NULL)	return false;
	
	int* v[elementos];
	
	int* c = vd;
	for (int i = 0; i < elementos; i++){
		*c = i;
		v[i] = c;
		c++;
	}   
    for (size_t i = 0; i < elementos - 1; i++) 
    {
      size_t j = i + (size_t)rand() / (size_t)(RAND_MAX / (elementos - i) + 1);
      int* t = v[j];
      v[j] = v[i];
      v[i] = t;
    }
    
	heap_sort((void**)v, elementos, cmp);
	for (size_t i = 0; i < elementos; i++){
		if (*(int*)v[i] != (int)i) {
		    free(vd);
		    return false;
		}
	}
	free (vd);
	return true;
}

int intcmp(const void* a, const void* b) {
	int* uno = (int*)a;
	int* dos = (int*)b;
	if (*uno > *dos) return 1;
	else if (*uno == *dos) return 0;
	return -1;
}


void pruebas_heap_alumno(void){
	int uno = 7;	int dos = 10;
	int tres = 4;	int cuatro = 5;
	int cinco = 20; int seis = 50;
	heap_t* heap = heap_crear(intcmp);
	print_test("Heap creado", (heap != NULL));
	print_test("Prueba desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("Prueba heap vacio", heap_esta_vacio(heap));
	print_test("Prueba ver maximo es NULL", heap_ver_max(heap) == NULL);
	heap_destruir(heap, NULL);
	heap = heap_crear(intcmp);
	print_test("Prueba encolar 7 es true", heap_encolar(heap, &uno) == true);
	print_test("Prueba ver maximo es 7", heap_ver_max(heap) == &uno);
	print_test("Prueba desencolar devuelve 7", heap_desencolar(heap) == &uno);
	print_test("Prueba encolar 10 es true", heap_encolar(heap, &dos));
	print_test("Prueba ver maximo del heap es 10", heap_ver_max(heap) == &dos);
	print_test("Prueba encolar 4 es true", heap_encolar(heap, &tres));
	print_test("Prueba ver maximo es 10", heap_ver_max(heap) == &dos);
	print_test("Prueba desencolar es 10", heap_desencolar(heap) == &dos);
	print_test("Prueba ver maximo es 4", heap_ver_max(heap) == &tres);
	print_test("Prueba desencolar es 4", heap_desencolar(heap) == &tres);
	heap_destruir(heap, NULL);
	heap = heap_crear(intcmp);
	print_test("Prueba encolar 7 es true", heap_encolar(heap, &uno));
	print_test("Prueba ver el maximo del heap es 7", heap_ver_max(heap) == &uno);
	print_test("Prueba encolar 10 es true", heap_encolar(heap, &dos));
	print_test("Prueba ver el maximo del heap es 10", heap_ver_max(heap) == &dos);
	print_test("Prueba encolar 4 es true", heap_encolar(heap, &tres));
	print_test("Prueba ver maximo del heap es 10", heap_ver_max(heap) == &dos);
	print_test("Prueba encolar 5 es true", heap_encolar(heap, &cuatro));
	print_test("Prueba el maximo del heap es 10", heap_ver_max(heap) == &dos);
	print_test("Prueba encolar 20 es true", heap_encolar(heap, &cinco));
	print_test("Prueba ver maximo del heap es 20", heap_ver_max(heap) == &cinco);
	print_test("Prueba encolar 50 es true", heap_encolar(heap, &seis));
	print_test("Prueba ver maximo del heap es 50", heap_ver_max(heap) == &seis);
	heap_destruir(heap, NULL);
		print_test("Heap destruido", true);
	print_test("Prueba Heapsort", prueba_heapsort(250, intcmp));
}
