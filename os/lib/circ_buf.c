#include "lib/klib.h"
#include "lib/circ_buf.h"


void circ_buf_init(circ_buf_t *buf, uint8_t *buf_start, uint32_t elem_size,
		   uint32_t size, uint8_t overwriting)
{
	buf->start = buf_start;
	buf->elem_size = elem_size;
	buf->size = size;
	buf->overwriting = overwriting;

	buf->count = 0;
	buf->head = buf_start;
	buf->tail = buf_start;
}

void circ_buf_pop(circ_buf_t *buf, void *elem)
{
	/* Buffer empty */
	if(buf->count == 0) {
		return NULL;
	}

	/* Get element */
	memcpy(elem, buf->tail, buf->elem_size);

	/* Move tail */
	buf->tail += buf->elem_size;
	buf->count--;


	/* If at end, move to start */
	if(buf->tail == (buf->start + buf->elem_size * buf->size)) {
		buf->tail = buf->start;
	}

	/* Return elem */
	return elem;
}



void circ_buf_push(circ_buf_t *buf, void *elem)
{
	/* If buffer full */
	if(buf->count == buf->size) {
		/* Check if we can overwrite end */
		if(buf->overwriting == 0) {
			return;
		} else {
			/* Move tail */
			buf->tail += buf->elem_size;
			/* If at end of buffer, wrap around */
			if(buf->tail == (buf->start + (buf->elem_size *
						       buf->size))) {
				buf->tail = buf->start;
			}
		}
	}


	/* Set element, move head and increment counter */
	memcpy(buf->head, elem, buf->elem_size);
	buf->head += buf->elem_size;
	buf->count++;

	/* Wrap head around, if at end of buffer */
	if(buf->head == (buf->start + (buf->elem_size * buf->size))) {
		buf->head = buf->start;
	}
}

