#!/bin/bash

echo "cd"
echo "cd #comment"
echo "cd -"
echo "cd bin"
echo "cd nonexistentfolder"
echo "mkdir test && cd test"
echo "(cd && ls -a) || echo A"
echo "echo A || cd -"
echo "cd - || echo B"
echo "echo C && cd folder"
echo "test main.cpp || cd bin"
echo "cd bin && cd -"
echo "cd bin #hello"
echo "[ -e bin ] && (cd bin && cd bin)"
echo "echo A && cd - && cd bin && cd - && cd"
echo "cd random || echo A && cd"
echo "cd bin && exit"

cd ..
bin/rshell << EOF

cd
cd #comment
cd -
cd bin
cd nonexistentfolder
mkdir test && cd test
(cd && ls -a) || echo A
echo A || cd -
cd - || echo B
echo C && cd folder
test main.cpp || cd bin
cd bin && cd -
cd bin#hello
[ -e bin ] && (cd bin && cd bin)
echo A && cd - && cd bin && cd - && cd
cd random || echo A && cd
cd bin && exit

exit
EOF
