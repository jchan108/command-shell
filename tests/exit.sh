#!/bin/bash


cd ..

bin/rshell << EOF
echo hello && exit
EOF

bin/rshell << EOF
exit
EOF

bin/rshell << EOF
echo hey && exit
EOF

bin/rshell << EOF
ls -a && exit
EOF

bin /rshell << EOF
(test bin && test Test.cpp) && exit
EOF

bin /rshell << EOF
[ -e bin ] && exit
EOF




EOF