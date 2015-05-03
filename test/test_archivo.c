/*
 * test_suite1.c
 *
 *  Created on: 12/4/2015
 *      Author: Alejandro Zalazar
 */

#include <string.h> /* memset */
#include <unistd.h> /* close */
#include <CUnit/CUnit.h>

#include "cunit_tools.h"

#include "../src/archivo.h"

static char* path = "prueba.txt";
static FILE* archivo = NULL;

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

static int inicializar() {
	unlink(path); //borra el archivo
	archivo = fopen(path, "w+");
	return archivo != NULL ? 0 : -1;
}

static int limpiar() {
	fclose(archivo);
	return unlink(path);
}

static void test_contar_devuelve_menos1_si_el_archivo_no_existe() {
	int cantidad = archivo_contar("askjd.txt", 'f');
	CU_ASSERT_EQUAL(cantidad, -1);
}

static void test_contar_devuelve_el_numero_exacto_de_ocurrencias() {
	inicializar();
	FILE* archivo = fopen(path, "w+");
	fprintf(archivo, "aca hay como 4 as");
	fflush(archivo); //para que se guarde en disco ahora
	int cantidad = archivo_contar(path, 'a');
	CU_ASSERT_EQUAL(cantidad, 4);
	limpiar();
}

static void test_contar_devuelve_0_si_no_hay_ocurrencias() {
	inicializar();
	fprintf(archivo, "no escribo ninguna equis"); fflush(archivo);
	int cantidad = archivo_contar(path, 'x');
	CU_ASSERT_EQUAL(cantidad, 0);
	limpiar();
}

static CU_TestInfo tests[] = {
//	{ "Test 1a", test_contar_devuelve_menos1_si_el_archivo_no_existe },
//	{ "Test 1b", test_contar_devuelve_el_numero_exacto_de_ocurrencias },
//	{ "Test 1c", test_contar_devuelve_0_si_no_hay_ocurrencias },
	CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(archivo, "Tests de archivo", init_suite, clean_suite, tests)
