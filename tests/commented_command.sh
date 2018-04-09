#!/bin/bash

echo "echo Hello World #echo Goodbye"
echo "hello ## hey"
echo "echo hello && echo # hey"
echo "echo yes && #"
echo "ls -a #echo hello world"
echo "history; echo hello world; #comment"
echo "echo hello"
echo "[ -e bin] && #comment"
echo "test -f #main.cpp"
echo "test -d anything #hi"
echo "[ bin ] || echo #hey"
echo "[ #main.cpp ]"
echo "[ -f main.cpp #here ]"
echo "echo world && #[ -e test.h ]"

cd ..
bin/rshell << EOF

echo Hello World #echo Goodbye
hello ## hey
echo hello && echo # hey
echo yes && #
ls -a #echo hello world
history; echo hello world; #comment
ls -a; #hello there
echo #hello
[ -e bin] && #comment
test -f #main.cpp
test -d anything #hi
[ bin ] || echo #hey
[ #main.cpp ]
[ -f main.cpp #here ]
echo world && #[ -e test.h ]


exit
EOF

