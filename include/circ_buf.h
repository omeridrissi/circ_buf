#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CIRC_CNT(head,tail,size) (((head) - (tail)) & ((size)-1))

#define CIRC_SPACE(head,tail,size) CIRC_CNT((tail),((head)+1),(size))

#define CIRC_CNT_TO_END(head,tail,size) \
	({int end = (size) - (tail); \
	  int n = ((head) + end) & ((size)-1); \
	  n < end ? n : end;})

#define CIRC_SPACE_TO_END(head,tail,size) \
	({int end = (size) - 1 - (head); \
	  int n = (end + (tail)) & ((size)-1); \
	  n <= end ? n : end+1;})

typedef struct {
	char *buffer;
	size_t size;
	size_t head;
	size_t tail;
} CircBuf;

enum CircErr {
	ECOUNT_TOO_LARGE = 1,
	ESIZE,
};

CircBuf circbuf_alloc(size_t size); 
void circbuf_free(CircBuf *circbuf); 

int circbuf_write(const char* src, CircBuf *circbuf, size_t count); 
int circbuf_read(char* dst, CircBuf *circbuf, size_t count);
