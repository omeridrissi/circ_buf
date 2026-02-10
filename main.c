#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circ_buf.h"


int main(void) {

	CircBuf circbuf = circbuf_alloc(16);
	const char *src = "hello";
	circbuf_write(src, &circbuf, strlen(src));
	printf("circbuf->buffer: %s\n", circbuf.buffer);
	char dst[20];

	circbuf_read(dst, &circbuf, strlen(src));

	printf("dst: %s\n", dst);

	circbuf_free(&circbuf);

	return 0;
}
