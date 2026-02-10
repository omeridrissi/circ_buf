#include <stdio.h>
#include <string.h>
#include "circ_buf.h"


int main(void) {

	CircBuf circbuf = circbuf_alloc(20);
	const char *src = "hello";

	circbuf_write(src, &circbuf, strlen(src));

	char dst[20];

	circbuf_read(dst, &circbuf, sizeof(src));

	printf("read ring buffer: %s\n", dst);

	return 0;
}
