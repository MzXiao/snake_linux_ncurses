default: build_singlethread

build_multithread:
	gcc -o bin/snake source/snake.c  -g -lncurses -lpthread -D MULTI_THREAD

build_singlethread:
	gcc -o bin/snake source/snake.c  -g -lncurses


run: build_singlethread
	./bin/snake
clean:
	rm -rf bin/*
