# Ring Buffer features

```c
//Allocate buffer
CircBuf circbuf_alloc(size_t size)

//Free buffer
void circbuf_free(CircBuf *circbuf);

// Read/Write buffer
int circbuf_read(const char *src, CircBuf *circbuf, size_t count);
int circbuf_write(char *dst, CircBuf *circbuf, size_t count); 

```

