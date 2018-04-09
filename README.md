# This is our project to create a command shell in C++

## RSHELL

### Authors: Joshua Chang, Anthony De Belen

## Functions

This program outputs the command line prompt   
  
`$`  
  
  
and  takes an input of commands in various forms including:  
  * Single Commands  
  
`$ ls -a;`  
  
`$ echo hello`  
  
`$ mkdir test`  
  
  * Multiple Commands separated by connectors  
  
`$ echo hi || echo hello && echo yes; mkdir yay`  
  
  * Exit command which just exits the program  
  
`$ exit`  
  
  * Test Command that shows if the file/directory exists  
`$ test -e bin or [ -e bin ]`  
  
  * Precedence command ()  
  
`$ (echo hi && echo hello) || echo world`

## Project Overview

We start off by putting almost the entirety of our main class inside a **do-while** loop.  
  
    do {
        Container *contain = new Container();
        contain->read();
    
        if(contain->userinput == "exit") {
        run = 0;
        } 
        else {
        contain->parse();
        contain->execute();
        }
        
    }while(run != 0);
  
where *run* is our variable that holds the value that would exit our loop if **exit** is our input. 
Doing so allows us to be able to immediately stop the whole program in the case the user decides to exit as seen in this line:  
  
`$ exit`  
  
We created a container class that holds many vectors and arrays which are listed below:  
  
  * **charVector** - vector that holds the tokenized parts  
  
`vector <string> charVector;`  
  
  * **Parsedlist** - vector for pointer to stringconnector which parses the input command into groups of format  
$ [executable] [arguement] [connector]  
  
`vector <stringconnector*> Parsedlist;`  
  
  * **aoc** - an array that holds the parsed strings as characters that will be used for the **execvp** system call.  
  
`char* aoc[3]`  
  
these vecotrs are needed to run multiple commands like:  
  
`$ mkdir test || echo no`  
  
parse them into separate tokens using the [**boost.tokenizer class**](http://www.boost.org/doc/libs/1_55_0/libs/tokenizer/tokenizer.htm), and finally execute them one by one using the fork
command seen here:  
  
                pid_t pid;  // the child process that the execution runs inside of.
                int stat;      // exit status of child process.
                pid = fork();
                if (pid == -1)
                { //A problem has occured with the forking call.
                }
                else if (pid == 0){
                    //execvp executes the command stored in aoc[0] over aoc    
                    execvp(aoc[0], aoc);
                    perror("exec");
                    exit(-1);
                }
                //pid > 1, thus we are in the parent's process
                else {
                    if( waitpid( pid, &stat, 0 ) == -1 ) {
                        perror( "waitpid" );
                    }
                    else if( WIFEXITED(stat) && WEXITSTATUS(stat) != 0 ) {
                        //if it reaches this branch the child fails
                        didcommandexecute = false;
                    }
                }  
  
Then we make sure it reads the connectors listed below:  
  
**&&** - If **cmd1** is *false*, then skip **cmd2** or if **cmd1** is true then test **cmd2** if it is true.
  
**||** - If **cmd1** is true, then skip **cmd2** or if **cmd1** is false then test **cmd2**.
  
**;** - Just run the command!!!  
  
The program should be able to do error checking like:
  
`$ ech hello`  
  
`ech: command not found`  
  
to see if all test case were dealt with.  
  
As of 11/14/2016, we have added the test command that outputs the string (True)  
if the specified file/directory does exist. Here is an example:  
  
`$ test -e bin`  
  
This function should be in an if statement to check if test or the open bracket [  
is found therefore, implementing the test command which we separately written its  
function so it does not go to execvp.  
  
The input above will output the string (True) because that directory does exist.  
We can also handle its other form which is shown here:  
  
`$ [ -e bin ]`  
  
which is exactly the same as the above statement.  
  
  
Next, we have added the precedence operator which runs the commands based on its precedence  
in the command line. Commands inside the parenthesis will be handled first before the  
operators outside. The trick is to add a checker in the parsing function so when it sees the  
parenthesis, it will know that the commands inside will take priority in being executed before  
the rest while still checking the operators if necessary. Here is an example:  
  
`$ (echo hi && echo hello) || echo world`  
  
which outputs

`hi`  
  
`hello`  
  
As of 11/28/2016, we have added the cd command whose purpose is navigate through the directories.  
We have two environment variables PWD and OLDPWD which hold the paths for each execution of the cd  
command. Here is an example for the cd command:  
  
`$ cd bin`  
  
if the folder bin exists, this command will update the current environment path to be \oldpath\bin  
but if the folder does not exist, it will print an error message. For this new cd function, we were  
to include three functionality namely:  
  
`cd`  
  
`cd -`  
  
`cd <PATH>`  
  
and each command should still work with the past functionality we had before including the test command  
and normal execvp commands.
  


## KNOWN BUGS

### Error Message

Commands and operands appear to work but a known bug in our program is that it can't mimick the error message given by unknown command in putty which is:  
  
`$ ech hello`  
  
`-bash: ech: command not found`  
  
but in our program we get this message just by using **perror**:  
  
`$ ech hello`  
  
`exec: no such file or directory`  
  
### Two Spaces

In our program we did not handle two white spaces before or after an operand therefore it gives an out of range error as seen here:  
  
`$ echo  hello`  
  
    terminate called after throwing an instance of 'std::out_of_range'
    what():  basic_string::at
    Aborted  
  
### Two semi-colons(;;)

Another known bug is having two semi-colons anywhere in the command line which should give a syntax error like this:  
  
`echo hello;; echo hi`  
  
`bash: syntax error near unexpected token `;;'`  
  
but in our program it still executes both commands:  
  
`$ echo hello;; echo hi`  
  
`hello;`  
  
`hi`  
  
### Three Operands(&&& or |||)

Same as the previous bug is if there are more than two symbols for each of our conditional statements/connectors. Here is what it looks like in putty:  
  
`$ echo hi &&& echo hello`  
  
`bash: syntax error near unexpected token `&'`  
  
but in our program it also runs it and iputs the following:  
  
`$ echo hi &&& echo hello`  
  
`hi &&& echo hello`  
  
### Commenting bug(#)

We noticed that when we run this command line in putty:   
  
`$ echo hi && #`  
  
it prompts us to type something because we guessed it wanted us to add something but in our program it runs normally so we get this output:  
  
`$ echo hi && #`  
  
`hi &&`  
  
### Missing space before or after an operand

This bug is because our parsing method is not perfect, therefore if we run this command in putty we get:  
  
`$ echo hi&& echo hello`  
  
`hi`  
  
`hello`  
  
but in our program it concatenates the whole line because the whitespace was missing which is the main core of our parsing method as seen here:  
  
`$ echo hi&& echo hello`  
  
`hi&& echo hello`  
  
asd



