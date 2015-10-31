test:module_test
	./module_test
module_test:so
	gcc b.c -ldl -o module_test
so:
	gcc -c m1.c	
	gcc -c m2.c	
	gcc -shared -fPIC -o m1.so m1.o
	gcc -shared -fPIC -o m2.so m2.o
clean:
	rm *.o *.so module_test
