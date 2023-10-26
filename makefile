build: 
	cc -o life src/main.c -L/usr/lib -lX11

clean: 
	rm life test

deploy: 
	cp life /usr/local/bin/life

test:
	cc -o test_life tests/test_life.c
	cc -o test_parser tests/test_parser.c
	./test_life
	./test_parser
