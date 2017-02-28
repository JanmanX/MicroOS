#include <lib/klib.h>
#include <stdint.h>
#include "test.h"

/* Free memory area for testing */
uint8_t buffer[BUFFER_SIZE];


void tests_run()
{
	if(test_memcmp()) {
		ERROR("TEST_MEMCMP() FAILED");
	} else {
		ERROR("MEMCMP TEST PASSED!");
	}

}


uint8_t test_memcmp()
{
	/* Errors */
	uint8_t e = 0;

	/* Create testing area */
	memcpy(buffer, "AAABBBCCC", 9);

	if(memcmp(buffer, "A", 1) != 0) {
		DEBUG("TEST FAILED!");
		e++;
	}

	if(memcmp(buffer, "B", 1) == 0) {
		DEBUG("TEST FAILED!");
		e++;
	}
	if(memcmp(buffer, "ABB", 1) != 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "AAA", 3) != 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "AAABBBCCC", 9) != 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "AAABBBCCD", 9) == 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "VASD", 1) == 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "D", 100) == 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "BAABBBCCC", 9) == 0) {
		e++;
		DEBUG("TEST FAILED!");
	}
	if(memcmp(buffer, "A", 1) != 0) {
		e++;
		DEBUG("TEST FAILED!");
	}

	return e;
}

