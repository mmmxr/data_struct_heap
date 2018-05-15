heap:heap.c
	gcc -o $@ $^

.PHONY:clean
	rm -f heap
