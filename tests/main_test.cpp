#include <CUnit/Basic.h>

// Forward declarations for test suites
extern void add_auth_tests(CU_pSuite pSuite);
extern void add_queries_tests(CU_pSuite pSuite);

// Forward declarations for suite initializers
extern int init_suite(void);
extern int clean_suite(void);
extern int init_queries_suite(void);
extern int clean_queries_suite(void);


int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry for Auth
    CU_pSuite pSuite_auth = CU_add_suite("Auth_Suite", init_suite, clean_suite);
    if (NULL == pSuite_auth) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // Add the tests to the suite
    add_auth_tests(pSuite_auth);

    // Add a suite to the registry for Queries
    CU_pSuite pSuite_queries = CU_add_suite("Queries_Suite", init_queries_suite, clean_queries_suite);
    if (NULL == pSuite_queries) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // Add the tests to the suite
    add_queries_tests(pSuite_queries);


    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    // Get number of failures
    unsigned int failures = CU_get_number_of_failures();

    CU_cleanup_registry();

    // Return error code if any tests failed
    return failures > 0 ? 1 : CU_get_error();
}
