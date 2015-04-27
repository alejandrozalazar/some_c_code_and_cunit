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

static void test_debe_listar_elementos_en_el_path_actual() {

	CU_ASSERT_TRUE(useLs() == 0);
}

static CU_TestInfo tests[] = {
	{ "Test ls", test_debe_listar_elementos_en_el_path_actual },
	CU_TEST_INFO_NULL,
};

CUNIT_MAKE_SUITE(system_calls_use, "Test llamadas al sistema", init_suite, clean_suite, tests)
