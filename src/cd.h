#include <iostream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <stdio.h>  //printf
#include <stdlib.h>  //stdi
using namespace std;


//also case of cd bin
bool cd(string a) {
    
//char *test = getenv("OLDPWD"); // at the start of the program, OLDPWD should be NULL.
char b2[MAXPATHLEN];
char *p2 = getcwd(b2, MAXPATHLEN); //   /home/ubuntu/workspace/CS100/practice 

    int rc = chdir(a.c_str()); // chdir changes current directory
    if (rc < 0) {
        perror("bash: cd: f: No such file or directory");
        return false;
    }
    
    else {
    char b3[MAXPATHLEN];
    char *p3 = getcwd(b3, MAXPATHLEN);
    
    setenv("OLDPWD", p2 , 1);
    setenv("PWD", p3 , 1);
    }

return true;
}

//case of cd -
bool cd2() {
    
char *test = getenv("OLDPWD"); // at the start of the program, OLDPWD should be NULL.
//char b2[MAXPATHLEN];
//char *p2 = getcwd(b2, MAXPATHLEN); //   /home/ubuntu/workspace/CS100/practice 



  if (test == NULL) { // if the OLDPWD is not set, test = NULL.
        cout << "bash: cd: OLDPWD not set" << endl;
    return false;
  }
    char b5[MAXPATHLEN];
    char *p5 = getcwd(b5, MAXPATHLEN);
    int d = chdir(test); // cd to oldpwd
    if (d < 0) {
        return false;
    }
    else {
    setenv("OLDPWD", p5  , 1);
    setenv("PWD", test , 1);
    }
    return true;
}
//home
bool cd3() {
//char *test = getenv("OLDPWD"); // at the start of the program, OLDPWD should be NULL.
char b2[MAXPATHLEN];
char *p2 = getcwd(b2, MAXPATHLEN); //   /home/ubuntu/workspace/CS100/practice 

 char * nPath;
 nPath = getenv("HOME");

int c = chdir(nPath); // chdir changes current directory
    if (c < 0) {
        return false;
    }
    else {
    char b4[MAXPATHLEN];
    char *p4 = getcwd(b4, MAXPATHLEN);
    
    setenv("OLDPWD", p2 , 1);
    setenv("PWD", p4 , 1);
    
    }
    
    return true;
}

