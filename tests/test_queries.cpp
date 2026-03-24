#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "queries.h"
#include "database.h"
#include <string>

// Stubs for suite initialization
extern int init_suite(void);
extern int clean_suite(void);

static Database* db_q = nullptr;
static QueryService* query_service = nullptr;

int init_queries_suite(void) {
    db_q = new Database("flotilla.db");
    query_service = new QueryService(*db_q);
    return 0;
}

int clean_queries_suite(void) {
    delete query_service;
    delete db_q;
    return 0;
}

void test_add_crew_member(void) {
    bool result = query_service->add_crew_member("Тестов", "sailor", "2025-01-01", 2005);
    CU_ASSERT_TRUE(result);
    auto db_result = db_q->query("SELECT * FROM CREW WHERE surname = 'Тестов';");
    CU_ASSERT_EQUAL(db_result.size(), 1);
}

void test_delete_crew_member(void) {
    query_service->add_crew_member("НаУдаление", "cook", "2025-01-01", 2005);
    bool result = query_service->delete_crew_member("НаУдаление");
    CU_ASSERT_TRUE(result);
    auto db_result = db_q->query("SELECT * FROM CREW WHERE surname = 'НаУдаление';");
    CU_ASSERT_EQUAL(db_result.size(), 0);
}

void test_update_crew_member(void) {
    query_service->add_crew_member("СтароеИмя", "cook", "2025-01-01", 2005);
    bool result = query_service->update_crew_member("СтароеИмя", "НовоеИмя");
    CU_ASSERT_TRUE(result);
    auto db_result_old = db_q->query("SELECT * FROM CREW WHERE surname = 'СтароеИмя';");
    auto db_result_new = db_q->query("SELECT * FROM CREW WHERE surname = 'НовоеИмя';");
    CU_ASSERT_EQUAL(db_result_old.size(), 0);
    CU_ASSERT_EQUAL(db_result_new.size(), 1);
}


// Function to add tests to the suite
void add_queries_tests(CU_pSuite pSuite) {
    if (NULL != pSuite) {
       CU_add_test(pSuite, "test_add_crew_member", test_add_crew_member);
       CU_add_test(pSuite, "test_delete_crew_member", test_delete_crew_member);
       CU_add_test(pSuite, "test_update_crew_member", test_update_crew_member);
    }
}
