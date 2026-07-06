#ifndef UNIT_TEST_API_H
#define UNIT_TEST_API_H


#ifdef HAS_FILE_API
#include "file_api_mcal.h"
#endif

#ifdef HAS_FILE_API
#define TEST_LOG_FILE_NAME   LOG_ERROR(SYS, "File:[%s]", file_path_to_file_name(__FILE__));
#else
#define TEST_LOG_FILE_NAME
#endif

#include "log.h"
#include "unit_test_assert.h"
#include "unit_test_expect.h"

#ifndef HAS_UNIT_TEST
#error "+HAS_UNIT_TESTS"
#endif

#ifndef HAS_LOG
#error "Add LOG component"
#endif

#endif /* UNIT_TEST_API_H */
