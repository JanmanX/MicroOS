#include <stdint.h>

#include "klib.h"


void itoa(char *buf, int base, int64_t n)
{
	char *p = buf;
	char *p1, *p2;
	uint64_t un = n;
	int div = 10;

	if(base == 'd' && n < 0) {
		*p++ = '-';
		un = -n;
		buf++;
	} else if (base == 'x') {
		div = 16;
	}

	do {
		/* calculate remainder */
		int r = un % div;

		*p++ = (r < 10) ? r + '0' : r + 'a' - 10;
	} while(un /= div);

	/* Terminate string */
	*p = 0;

	/* Reverse the string */
	p1 = buf;
	p2 = p - 1;


	while(p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;

	}
}
