CC=gcc
CFLAGS=-O3 -g
 
TARGET=test mandel
 
all: $(TARGET)
 
libppm.so : ppm.c  # Compile PPM lib to libppm.so
	$(CC) $(CFLAGS)  -fpic -shared $^ -o $@
 
test: main.c libppm.so  # Compile test executable 
	$(CC) $(CFLAGS) $(LDFLAGS) main.c  -lppm -L. -o $@

mandel: mandel.c libppm.so  # Compile mandelbrot code source
	$(CC) $(CFLAGS) $(LDFLAGS) $< -lppm -L.  -o $@
 
.PHONY: clean
clean:
	rm -fr $(TARGET) *.so
