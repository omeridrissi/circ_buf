#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circ_buf.h"

CircBuf circbuf_alloc(size_t size) {
	CircBuf new_circbuf;

	// Check if size is a power of 2
	assert((size & (size - 1)) == 0);

	new_circbuf.buffer = malloc(sizeof(char*)*size);
	new_circbuf.size = size;
	new_circbuf.head = 0;
	new_circbuf.tail = 0;

	return new_circbuf;
}

void circbuf_free(CircBuf *circbuf) {
	free(circbuf->buffer);
}

int circbuf_write(const char* src, CircBuf *circbuf, size_t count) {
	if (count > CIRC_SPACE(circbuf->head, circbuf->tail, circbuf->size)) {
		return -ECOUNT_TOO_LARGE;
	}

	size_t space_to_end = CIRC_SPACE_TO_END(circbuf->head, circbuf->tail, circbuf->size);
	
	if (space_to_end >= count) {
		for (size_t i = 0; i < count; ++i) {
			circbuf->buffer[i + circbuf->head] = src[i];			
		}
		circbuf->head += count;
	} else {
		size_t diff = count - space_to_end;
		size_t i = 0;
		for (; i < space_to_end; ++i) {
			circbuf->buffer[i + circbuf->head] = src[i];
		}
		circbuf->head = 0;
		for (; i < space_to_end+diff; ++i) {
			circbuf->buffer[i - space_to_end] = src[i];
		}
		circbuf->head = diff;
	}

	return 0;
}

int circbuf_read(char* dst, CircBuf *circbuf, size_t count) {
	if (count > CIRC_CNT(circbuf->head, circbuf->tail, circbuf->size)) {
		return -ECOUNT_TOO_LARGE;
	}

	size_t cnt_to_end = CIRC_CNT_TO_END(circbuf->head, circbuf->tail, circbuf->size);
	
	if (cnt_to_end >= count) {
		for (size_t i = 0; i < count; ++i) {
			dst[i] = circbuf->buffer[i + circbuf->tail];
		}
		circbuf->tail += count;
	} else {
		size_t diff = count - cnt_to_end;
		size_t i = 0;
		for (; i < cnt_to_end; ++i) {
			dst[i] = circbuf->buffer[i + circbuf->tail];
		}
		circbuf->tail = 0;
		for (; i < cnt_to_end+diff; ++i) {
			dst[i] = circbuf->buffer[i - cnt_to_end];
		}
		circbuf->tail = diff;
	}

	return 0;
}
