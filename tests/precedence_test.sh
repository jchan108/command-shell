#!/bin/bash

echo "echo hi || (ls -a && echo hello)"
echo "(echo yay)"
echo "(echo hello && ps) || (echo good && echo bye)"
echo "((echo hi))"
echo "(echo hey) && (echo there)"
echo "(mkdir test && echo beep || echo boop) || echo boom"
echo "echo hi; (echo yes || echo no)"
echo "(echo open; echo close || echo door) && rm -r"
echo "((mkdir test && echo test) || (mkdir test2 && echo test2))"

cd ..
bin/rshell << EOF

echo hi || (ls -a && echo hello)
(echo yay)
(echo hello && ps) || (echo good && echo bye)
((echo hi))
(echo hey) && (echo there)
(mkdir test && echo beep || echo boop) || echo boom
echo hi; (echo yes || echo no)
(echo open; echo close || echo door) && rm -r
((mkdir test && echo test) || (mkdir test2 && echo test2))

exit
EOF