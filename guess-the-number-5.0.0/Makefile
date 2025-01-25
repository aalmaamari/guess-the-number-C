CC = clang
CFLAGS = -Iinclude

SRC = src/main.c  src/setter.c src/guesser.c
APP = build/app

app: $(SRC)
	$(CC) $(CFLAGS) -o $(APP) $(SRC)


run:
	./build/app


clean:
	rm ./build/app