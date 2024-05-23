default: build

build:
	gcc irregex.c -o irregex
	./irregex "hello .*;" "hello nosferatu; hello ninthcircle"

clean:
	rm irregex
