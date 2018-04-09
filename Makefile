flag = -Wall -Werror -ansi -pedantic

rshell:
	mkdir -p bin
	g++ $(flag) src/main.cpp -o bin/rshell
