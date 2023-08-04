build: 
	cc -o life src/main.c -L/usr/lib -lX11

clean: 
	rm life test

deploy: 
	cp life /usr/local/bin/life

test: test.c src/
	cc -o test test.c 
