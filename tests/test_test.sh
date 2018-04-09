#!/bin/bash

echo "test -e bin"
echo "test bin"
echo "test -e bin && echo hi"
echo "test bin && test anything"
echo "test -f main.cpp && test -d Container.h"
echo "[ -f bin ]"
echo "[ -d bin ] && echo world"
echo "[ -d .git ] || (echo hello && echo world)"
echo "[ anything ] || (echo is && echo True"
echo "mkdir test && [ -e test ]"
echo "[ -f main.cpp ] && ls -a"
echo "echo uhhhh; test -e Makefile"

cd ..
bin/rshell << EOF

test -e bin
test bin
test -e bin && echo hi
test bin && test anything
test -f main.cpp && test -d Container.h
[ -f bin ]
[ -d bin ] && echo world
[ -d .git ] || (echo hello && echo world)
[ anything ] || (echo is && echo True
mkdir test && [ -e test ]
[ -f main.cpp ] && ls -a
echo uhhhh; test -e Makefile


exit
EOF