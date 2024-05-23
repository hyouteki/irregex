default: build

build:
	gcc irregex.c -o irregex

test:
	irregex "Hello .* " "Hello nosferatu Hello ninthcircle"
	irregex "ir*e.ex" "irrrrrregex"

clean:
	rm irregex
