#ifndef CIRC_BUF_H
#define CIRC_BUF_H
#include <stdint.h>

/*
 *                                size
 *                                  ^
 *                                  |
 * +--------------------------------+-------------------------------+
 * |                                                                |
 * +                                                                +
 *
 * start
 * +                      elem_size
 * |                      ^                                   start + size
 * v                    +-+--+                                      ^
 *                      |    |                                      |
 * +----------------------------------------------------------------+
 * |                    |    |                                      |
 * +-------------------------+-----------------------------+--------+
 *                      ^                                  ^
 *                      |                                  |
 *                      +                                  +
 *                      tail                               head
 */


typedef struct circ_buf {
	uint64_t	elem_size;	/* Size of each element. (mod 8) */
	uint8_t		*start;		/* Start of the buffer */
	uint64_t	size;		/* Size of the buffer in elements */
	uint64_t	count;		/* Current number of elements in buf */

	uint8_t		overwriting;	/* Determines of elements are
					   overwritten from the end. */


	uint8_t		*head;		/* Head of the buffer */
	uint8_t		*tail;		/* Tail of the buffer */

} circ_buf_t;


void circ_buf_init(circ_buf_t *buf, uint8_t *buf_start, uint32_t elem_size,
		   uint32_t size, uint8_t overwriting);

void circ_buf_pop(circ_buf_t *buf, void* elem);
void circ_buf_push(circ_buf_t *buf, void *elem);




#endif /* CIRC_BUF_H */
