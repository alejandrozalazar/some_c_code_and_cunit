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

#include "../src/otro_archivo.h"

static int init_suite() {
	return 0;
}

static int clean_suite() {
	return 0;
}

static void test_debe_devolver_hola_mundo() {
	CU_ASSERT_STRING_EQUAL("Hola Mundo", decirHolaMundo());
}

static CU_TestInfo tests[] = {
	{ "Test 1b", test_debe_devolver_hola_mundo },
	CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(otro_archivo, "Test otro archivo", init_suite, clean_suite, tests)
