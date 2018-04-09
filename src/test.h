
#include <sys/stat.h>
#include <iostream>
#include <string>
using namespace std;



//tests if it exists as a file
bool File(char* filetype)
{
    struct stat file; 
    if ( stat(filetype, &file) ) {
    return false;
    }
    
    if ( !S_ISREG(file.st_mode) ) {
    return false;
    }
    
    //if both the false checks fail, it must be true
    return true;
}

//tests if it exists as a directory
bool Directory(char* filetype)
{
    struct stat file;
    if ( stat(filetype, &file) ) {
    return false;
    }
    
    if ( !S_ISDIR(file.st_mode) ) {
    return false;
    }
    
    //if both the false checks fail, then it must be true
    return true;
}

bool TestCommand(char * a) {
    //cout << a;
    
// the -e flag    
if (a[0] == '-' && a[1] == 'e' && a[2] == ' ') {
    //cout << "any" << endl;
    //cout << a << endl;
    a++;    a++;    a++;
    
if (File(a) == true || Directory(a) == true)  {
    cout << "(True)" << endl;
    return true;
}
else {
    cout << "(False)" << endl;
    return false;
}
    
}    
    
//the -d flag    
else if (a[0] == '-' && a[1]=='d' && a[2] == ' ') {
    //cout << "directory" << endl;
    a++; a++; a++;

if (Directory(a) == true) {
    cout << "(True)" << endl;
    return true;
} 
else {
    cout << "(False)" << endl;
    return false;
}
    
}    
    
//the -f flag    
else if (a[0] == '-' && a[1] == 'f' && a[2] == ' ') {
    //cout << "file" << endl;
    a++; a++; a++;
if (File(a) == true) {
    cout << "TRUE" << endl;
    return true;
}
else {
    cout << "FALSE" << endl;
    return false;
}
    
    
}

return true;
}














