#include "heap.h"
#include "testing.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CANT 1000

int cmp_int(const void* a, const void* b) {
	int* temp1 = (int*)a;
	int* temp2 = (int*)b;
	if (*temp1 > *temp2) return 1;
	else if (*temp1 < *temp2) return -1;
	return 0;
}

int cmp_inv(const void* a, const void* b) {
	int* temp1 = (int*)a;
	int* temp2 = (int*)b;
	if (*temp1 > *temp2) return -1;
	if (*temp1 < *temp2) return 1;
	return 0;
}

bool prueba_heapsort(size_t elementos, cmp_func_t cmp, bool inverso){
	int* lista  = malloc( sizeof(int) * elementos );
	if (lista == NULL)	return false;
	int* v[elementos];
	int* c = lista;
	for (int i = 0; i < elementos; i++){
		*c = i;
		v[i] = c;
		c++;
	}
    for (size_t i = 0; i < elementos - 1; i++){
		size_t j = i + (size_t)rand() / (size_t)(RAND_MAX / (elementos - i) + 1);
		int* t = v[j];
		v[j] = v[i];
		v[i] = t;
    }
	heap_sort((void**)v, elementos, cmp);
	if (inverso){
		for (size_t i = elementos; i > 0; i--){
			if (*(int*)v[i-1] != (int)(elementos-i)) {
			    free(lista);
			    return false;
			}
		}
	}
	else {
		for (size_t i = 0; i < elementos; i++){
			if (*(int*)v[i] != (int)i) {
		    	free(lista);
		    	return false;
			}
		}	
	}
	free (lista);
	return true;
}

bool heap_encolar_muchos(heap_t* heap, int* vec, size_t elem){
	for (int i = 0; i < elem; i++){
		*vec = i;
		if (!heap_encolar(heap, vec) || (*(int*)heap_ver_max(heap) != i)){	
			free(vec);
			return false;
		}
		vec++;
	}
	return true;
}

bool heap_desencolar_muchos(heap_t* heap, size_t elem){
	int* v = malloc(sizeof(int)*elem);
	if (!v)	return false;
	int* dato;
	for (int i = 0; i < elem; i++) {
		dato = (int*)(heap_desencolar(heap));
		if (!dato) {
			free(v);
			return false;
		}
		v[i] = *dato;
	}
	bool ok = true;
	for (size_t i = 0; i < elem; i++) {
		if ((elem-1-i) != v[i]) {
			ok = false;
			break;
		}
	}
	free(v);
	return ok;
}

void prueba_volumen(void){
	print_test("PRUEBAS HEAP ENCOLAR Y DESENCOLAR - VOLUMEN",true);
	heap_t* heap = heap_crear(cmp_int);
	int * v = calloc(CANT,sizeof(int));
	print_test("Prueba encolar muchos elementos", heap_encolar_muchos(heap, v, CANT));
	print_test("Prueba heap_cantidad es 1000", (int)heap_cantidad(heap) == CANT);
	print_test("Prueba desencolar muchos elementos", heap_desencolar_muchos(heap, CANT));
	print_test("Prueba heap_cantidad es 0", (int)heap_cantidad(heap) == 0);
	free(v);
	heap_destruir(heap, NULL);
	print_test("Heap destruido",true);
}

void pruebas_heapsort(void){
	print_test("PRUEBAS HEAPSORT",true);
	print_test("Prueba Heapsort", prueba_heapsort(CANT, cmp_int,false));
    print_test("Prueba Heapsort inverso", prueba_heapsort(CANT, cmp_inv, true)); //inverso
}

void prueba_desencolar_ver_max(void){
	print_test("PRUEBAS HEAP DESENCOLAR Y VER MAXIMO",true);
	int uno = 7;	
	int dos = 10;
	int tres = 4;
	heap_t* heap = heap_crear(cmp_int);
	print_test("Prueba ver maximo es NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba desencolar es NULL", heap_desencolar(heap) == NULL);
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
	print_test("Heap destruido",true);
}

void prueba_encolar_ver_max(void){
	print_test("PRUEBAS HEAP ENCOLAR",true);
	int uno = 7;	int dos = 10;
	int tres = 4;	int cuatro = 5;
	int cinco = 20; int seis = 50;
	heap_t* heap = heap_crear(cmp_int);
	print_test("Heap creado", (heap != NULL));
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
	print_test("Heap destruido",true);
}

void prueba_vacia(void){
	print_test("PRUEBAS HEAP",true);
	int uno = 7;
	heap_t* heap = heap_crear(cmp_int);
	print_test("Heap creado", (heap != NULL));
	print_test("Prueba heap vacio", heap_esta_vacio(heap));
	print_test("Prueba encolar es true", heap_encolar(heap, &uno));	
	print_test("Prueba heap vacio es false", !heap_esta_vacio(heap));
	print_test("Prueba desenconlar es true", heap_desencolar(heap) == &uno);
	print_test("Prueba heap vacio otra vez", heap_esta_vacio(heap));
	heap_destruir(heap, NULL);
	print_test("Heap destruido",true);
}

void prueba_heap_vector(void){
	print_test("PRUEBAS HEAP A PARTIR DE UN ARRAY",true);
	int v[]= {10,8,9,5,3,2,4,1,7,6};
	void ** vvp = calloc(10,sizeof(void*));
	for(size_t i= 0; i<10; i++){
		vvp[i] = &v[i];
	}
	heap_t* heap = heap_crear_arr(vvp,10,cmp_int);
	print_test("Heap creado a partir de un vector de 10 enteros desordenados",heap!=NULL);
	for (size_t i= 10; i>0; i--){
		int * pop =(int*) heap_desencolar(heap);
		print_test("Desencolando ordenado, mayor a menor", *pop == i);
	}
	heap_destruir(heap, NULL);
	print_test("Heap destruido",true);
	free(vvp);
}

void pruebas_heap_alumno(void){
	prueba_vacia();
	prueba_encolar_ver_max();
	prueba_desencolar_ver_max();
	prueba_volumen();
	pruebas_heapsort();
	prueba_heap_vector();
}
