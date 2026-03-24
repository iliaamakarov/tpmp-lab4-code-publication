#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "auth.h"
#include "database.h"
#include <string>

static Database* db = nullptr;
static AuthService* auth_service = nullptr;

int init_suite(void) {
    system("make db"); // Ensure a clean database for tests
    db = new Database("flotilla.db");
    auth_service = new AuthService(*db);
    return 0;
}

int clean_suite(void) {
    delete auth_service;
    delete db;
    return 0;
}

void test_successful_login(void) {
    User user = auth_service->login("captain", "password");
    CU_ASSERT_TRUE(user.isAuthenticated);
    CU_ASSERT_STRING_EQUAL(user.role.c_str(), "captain");
}

void test_failed_login(void) {
    User user = auth_service->login("captain", "wrongpassword");
    CU_ASSERT_FALSE(user.isAuthenticated);
}

void test_nonexistent_user_login(void) {
    User user = auth_service->login("nouser", "nopass");
    CU_ASSERT_FALSE(user.isAuthenticated);
}

// Function to add tests to the suite
void add_auth_tests(CU_pSuite pSuite) {
    if (NULL != pSuite) {
        CU_add_test(pSuite, "test_successful_login", test_successful_login);
        CU_add_test(pSuite, "test_failed_login", test_failed_login);
        CU_add_test(pSuite, "test_nonexistent_user_login", test_nonexistent_user_login);
    }
}
