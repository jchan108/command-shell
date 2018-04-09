#!/bin/bash

echo "echo hello && echo hey && echo what"
echo "echo hello || echo hi || echo hey"
echo "echo what && echo yo || echo yes; echo test"
echo "echo hey; echo what && echo yo || echo what"
echo "echo hello || echo hello && echo hello; echo hi haha"
echo "echo world; echo is; echo in; echo danger"
echo "echo you || echo know || echo the || echo asnwer"
echo "ls -a; echo hey; echo hi; echo && ls -a"
echo "echo hello; echo hi || echo no"
echo "echo i && echo am && echo dead && echo after; echo this"

cd ..
bin/rshell << EOF

echo hello && echo hey && echo what
echo hello || echo hi || echo hey
echo what && echo yo || echo yes; echo test
echo hey; echo what && echo yo || echo what
echo hello || echo hello && echo hello; echo hi haha
echo world; echo is; echo in; echo danger
echo you || echo know || echo the || echo asnwer
ls -a; echo hey; echo hi; echo && ls -a
echo hello; echo hi || echo no
echo i && echo am && echo dead && echo after; echo this

exit

EOF