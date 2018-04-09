#!/bin/bash

echo "Test Case 1 : echo hello"  # testing echo hello
echo "Test Case 2 : ls" # testing ls command
echo "Test Case 3 : date" #testing date command
echo "Test Case 4 : ls -a" #testing ls -a command
echo "Test Case 5 : history" #testing history command
echo "Test Case 5 : exit"


cd ..
bin/rshell << EOF
echo hello
ls
date
ls -a
history
exit

EOF