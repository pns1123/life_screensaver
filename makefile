build: 
	cc -o build/life src/main.c -L/usr/lib -lX11

clean: 
	rm build/*

deploy: 
	cc -o build/life src/main.c -L/usr/lib -lX11
	cp build/life /usr/local/bin/life

test:
	cc -o build/test_life tests/test_life.c
	cc -o build/test_parser tests/test_parser.c
	./build/test_life
	./build/test_parser
