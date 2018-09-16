CFLAGS= -pedantic -std=gnu99
maxSeq: test-subseq.o maxSeq.o
	gcc $(CFLAGS) -o maxSeq test-subseq.o maxSeq.o
maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c
