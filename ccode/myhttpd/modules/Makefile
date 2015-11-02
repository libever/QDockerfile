all:m.c n.c
	gcc -shared -fPIC -o m.so m.c -lmymodule -L ../ -I ../
	gcc -shared -fPIC -o n.so n.c -lmymodule -L ../ -I ../

clean:
	rm -f *.so
