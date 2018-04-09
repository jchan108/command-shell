#ifndef CONTAINER_H
#define CONTAINER_H
#include "Core.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <string.h>
#include "stringconnector.h"
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fstream>
#include "test.h"
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
#include <stdio.h>  
#include <stdlib.h>  
#include "cd.h"

using namespace boost;


class Container : public Core {
    protected:
    
    vector <string> charVector;
    vector <stringconnector*> Parsedlist;
    char** FinalArray[9999];
    char* aoc[3];     
//    int run = 1;
    
    public:
    int run;
    //constructor
    Container(){ run = 1;}
    ~Container(){}
    
    void read() {
        
   char buff[MAXPATHLEN]; 
   char *path2 = getcwd(buff, MAXPATHLEN); // gets our current directory
        
        cout << path2 << " $ "; 
        getline(cin,userinput);
    }
    void parse() { 
    
    string sep1("");
    string sep2(" ");
    string sep3(""); 

    escaped_list_separator<char> els(sep1,sep2,sep3);
    tokenizer<escaped_list_separator<char> > tok(userinput, els);
       
        for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
            charVector.push_back(*beg);
        }
       
        //for test purposes, not essential
        // for (int i = 0; i < charVector.size(); ++i) {
        //     cout << charVector.at(i) << endl;
        // }
    
        
        //reused variable j
        unsigned int j = 0;
        for (unsigned int i = 0; i < charVector.size(); ++i) {
   
            
            // if i goes to the last list element 
            if (i == charVector.size() - 1) {
                
                
            //if in the last element holds a ; need to get rid of it
            if(charVector.at(i).at(charVector.at(i).size() - 1) == ';') {
                charVector.at(i).erase(charVector.at(i).size()-1 , 1);
            }    
                
               
            if (j == i) {
                stringconnector* temp = new stringconnector(charVector.at(j),  "X");
                Parsedlist.push_back(temp);                 
            }  
            
            else {
                stringconnector* temp = new stringconnector(charVector.at(j), "X");
                j = j + 1;
                temp->specialpushback(charVector.at(j));
                
                for (j = j + 1; j <= i; ++j) {
                    temp->pushback(charVector.at(j));
                }
                
                Parsedlist.push_back(temp);
            }
                
            } // if last
            
            else if (charVector.at(i) == "&&" || charVector.at(i) == "||") {
                stringconnector* temp = new stringconnector(charVector.at(j),charVector.at(i));
                
                j = j + 1;
                temp->specialpushback(charVector.at(j));
                
                for (j = j + 1; j < i; ++j) {
                temp->pushback(charVector.at(j));
                }
                
                j = i + 1;
                Parsedlist.push_back(temp);
            } // if && or ||
            
          
            //if i reaches a semicolon
            else if(charVector.at(i).at(charVector.at(i).size() - 1) == ';') {
            // stringconnector* temp = new stringconnector(charVector.at(j),";");
            //string tempcolon = charVector.at(i);
            charVector.at(i).erase(charVector.at(i).size()-1 , 1);
            stringconnector* temp = new stringconnector(charVector.at(j),";");
            //inital pushback case
            //temp->specialpushback(charVector.at(j+1));
            
            j = j + 1;
            temp->specialpushback(charVector.at(j));
            
            // for (j= j + 1; j <= i; ++j) {
            //     temp->specialpushback(charVector.at(j));
            // }
            
            for (j= j + 2; j <= i; ++j) {
                temp->pushback(charVector.at(j));
            }
            
            j = i + 1;
            Parsedlist.push_back(temp);
            }//if ;
            
            

        }

    int index;
    // assignment 3 update
    //here we check for the () 
    for (unsigned int t = 0; t < Parsedlist.size(); ++t) {
    
    int outindex;
     if (Parsedlist.at(t)->argument.size() != 0) {
     outindex = Parsedlist.at(t)->argument.size() - 1;
     } else {
         break;
     }
    
        if (Parsedlist.at(t)->executable.at(0) == '(') {
        Parsedlist.at(t)->start = true;
        Parsedlist.at(t)->executable.erase(0,1);
        
       
        for (unsigned int b = t; b < Parsedlist.size(); ++b) {
            
                if (Parsedlist.at(b)->argument.size() != 0) {
                index = Parsedlist.at(b)->argument.size() - 1;
                }
                else {
                    break;
                }
                
                
            if(Parsedlist.at(b)->argument.at(index) == ')') {
                Parsedlist.at(b)->end = true;
                Parsedlist.at(b)->argument.resize(index);
                break;
            }
            else {
                if (Parsedlist.at(b)-> start != true) {
                Parsedlist.at(b)->mid = true;
                }
            }
            
            t = b;
        }
        
    }
    // inthe case that it is echo hello) program should stop
    else if (Parsedlist.at(t)->argument.at(outindex) == ')') {
        Parsedlist.resize(0);
        cout << "bash: syntax error near unexpected token `)'" << endl;
    }
      
    }//end of for
    //here we deal with the [    ] test case    
    //  cout << Parsedlist.at(0)->argument << endl;
    // cout << Parsedlist.at(0)->executable << endl;
        
    
    
    for (unsigned int r = 0; r < Parsedlist.size(); ++r) {
        
    // [ -e bin ] case (Case sensitive)    when it turns into parsedlist it turns to ex = [ , arg = -e bin ]
    if (Parsedlist.at(r)->executable.size() == 1 && Parsedlist.at(r)->executable.at(0) == '[' && Parsedlist.at(r)->argument.at(Parsedlist.at(r)->argument.size()-1) ) {
    
    string tempsauce = "";
    tempsauce.append(Parsedlist.at(r)->argument);
    tempsauce.erase(tempsauce.size()-2,2);
    Parsedlist.at(r)->argument = tempsauce;
    Parsedlist.at(r)->executable = "test";
    } 
     
     // [-e bin] case   
     if (Parsedlist.at(r)->executable.at(0) == '[' && Parsedlist.at(r)->argument.at(Parsedlist.at(r)->argument.size()-1)) {
         //cout << "HIII" << endl;
     string tempusauce = "";
     
     tempusauce.append(Parsedlist.at(r)->executable);
     tempusauce.erase(0,1);
     tempusauce.push_back(' ');
     tempusauce.append(Parsedlist.at(r)->argument);
    // tempusauce.pop_back();
    tempusauce.erase(tempusauce.size()-1,1);
     Parsedlist.at(r)->argument = tempusauce;
     Parsedlist.at(r)->executable = "test";
         
     }
    }    
    
    
    
    //in the case that it is of the form test bin, need to transofrm to test -e bin
    
    for (unsigned int r = 0; r < Parsedlist.size(); ++r ) {
        
        if (Parsedlist.at(r)->executable == "test" && Parsedlist.at(r)->argument.at(0) != '-') {
            string tempasauce = "";
            tempasauce.append("-e ");
            tempasauce.append(Parsedlist.at(r)->argument);
            Parsedlist.at(r)->argument = tempasauce;
        }
        
    }
    
    //bad program skills cover up
    for (unsigned int qq = 0; qq < Parsedlist.size(); ++qq) {
        
        if (Parsedlist.at(qq)->executable == "cd-") {
            Parsedlist.at(qq)->argument = "";
        }
        
    }
    
    // now we make the cd commands, all three  cases
    
        
    }
    
    void execute() {
 
        char cdcomp[] =  "cd";
        //char cdcomp2[] =  "cd-";
        char empty[] = "";
        char dash[] = "-";
        // comment catcher
        char testy[] = "test"; // for the test analysis
        
        for (unsigned int k = 0; k < Parsedlist.size(); ++k) {
            size_t found = Parsedlist.at(k)->argument.find("#");
            if (found == string::npos) {
                break;
            }
            //in the case that # is the first character of the string
            else if (found == 0) {
                Parsedlist.resize(1);
                Parsedlist.at(0)->argument = "";
                break;
            }
            //in the case that it is in the a #a form
            else if (Parsedlist.at(k)->argument.at(found-1) == ' ' ) {
                Parsedlist.resize(k+1);
                //maybe k-2?
                Parsedlist.at(k)->argument.resize(found-1);
                //maybe change connector to X here?
                break;
            }
            //in the case that it is in the echo a#a form
            else {
            

             
            unsigned int pos =  Parsedlist.at(k)->argument.find("#");
        
           
            
             while (pos != string::npos) {
            // // if it finds in the a #a form
        
             
                if (Parsedlist.at(k)->argument.at(pos-1) == ' ' ) {
                Parsedlist.resize(k+1);
                //maybe k-2?
                Parsedlist.at(k)->argument.resize(pos-1);
            
            }
            
        
              pos =  Parsedlist.at(k)->argument.find("#",pos+1);   
             }    
            
          
            }
        }
    
    //exit fixer
        for (unsigned int z = 0; z < Parsedlist.size(); ++z) {
            if (Parsedlist.at(z)->executable == "exit") {
             //   cout << "please";
                Parsedlist.resize(z);
                run = 0;
            }
        }
        
        
        //   cout << Parsedlist.at(0)->argument << endl;
        bool didcommandexecute = false;
        string prevcon = "Start";
        bool prevtruth = true;
        bool doexecute = true;
             
            //this for loop loops for each position in the parsed list
            //it creates
        
        // implementing the (echo helo && echo hi) here.
        bool inloop = false;
        //this gives truth value of entire (...)
        bool looptruth = false;
        
        bool performskip = false;
        
        for (unsigned int z = 0; z < Parsedlist.size(); z = z + 1) {
            
            
            if (Parsedlist.at(z)->start == true) {
            
            
                if (prevcon == "&&") {
                    if (prevtruth == false) {
                        //need to skip all the elements... until reaches )
                        performskip = true;
                    }
                    
                }   
                else if (prevcon == "||") {
                    if (prevtruth == true) {
                        //need to skip all the elements... until reaches )
                        performskip = true;
                    }
                }
            
            
                else {        
                inloop = true;
                }
            }
            
            //we now skip through the vector and erase elements.
            if (performskip == true) {
                
            
                
                for (unsigned int y = z; y < Parsedlist.size(); ++y) {
                    if (Parsedlist.at(y)->end == true) {
                        z = y;
                        prevcon = Parsedlist.at(y)->connector;
                        break;
                    }
                }
                
              performskip = false;    
              continue;
            }
            
            
            
            
            
            didcommandexecute = true;
            // cout << "testing this" << endl;
            //doexecute = true;
            unsigned int aa = Parsedlist.at(z)->executable.size(); 
            //cstring of executable
            //char* xnum = new char[aa+1];
            
            
            char* xnum = new char[aa+1];
            //char xnum[aa + 1];
            xnum[aa] = '\0';
            for (unsigned int ab = 0; ab < aa; ++ab) {
                xnum[ab] = Parsedlist.at(z)->executable.at(ab);
            } //for int ab
            //cstring of argument
            int ac = Parsedlist.at(z)->argument.size();
            //char* anum = new char[ac+1];
            char* anum = new char[ac+1];
            //char anum[ac + 1];
            anum[ac] = '\0';
             
            for (int ad = 0; ad < ac; ++ad) {
                anum[ad] = Parsedlist.at(z)->argument.at(ad);
            } //for int ad

        
            aoc[0] = xnum;
            aoc[1] = anum;
            aoc[2] = NULL;
               
            //  cout << aoc[0] << " : " << aoc[1] << endl; 
               
            if (prevcon == "Start" ) {
                doexecute = true;
            }
            
            else if (prevcon == "&&") {
                if (prevtruth == true) {
                    doexecute = true;
                }
                //truth = false
                else {
                    doexecute = false;
                }
            }
            
            else if (prevcon == "||") {
                if (prevtruth == true) {
                    doexecute = false;
                }
                else {
                    doexecute = true;
                }
                
            }
            
            else if (prevcon == ";") {
                doexecute = true;
            }
            
        //    cout << "PLEASE" << endl;
            
            // WE ONLY ATTEMPT AN EXECUTE IF DOEXECUTE IS TRUE
            if (doexecute == true) {
                //aoc[0] = cd
                if (strcmp(cdcomp,aoc[0]) == 0)  {
                    //aoc[1] is empty
                    if (strcmp(empty,aoc[1]) == 0) {
                    didcommandexecute = cd3();
                    }
                    //aoc[1] = a directory name
                    else if (strcmp(dash,aoc[1]) == 0) {
                   
                   didcommandexecute = cd2();
                    }
                   else {
                    string ele = aoc[1];
                    didcommandexecute = cd(ele);
                    }
                
                    
                }
                //aoc[0] = cd-
                // else if (strcmp(cdcomp2,aoc[0]) == 0) {
                //     didcommandexecute = cd2();
                // }
 
 
                // this tests if test == test
                else if (strcmp(testy,aoc[0]) == 0) {
                    //cout << "PLEASE" << endl;
                
                 didcommandexecute = TestCommand(aoc[1]);   
                     
                }
                else { 
                //HERE WE EXECUTE THE TEST CO
                
                pid_t pid;  // the child process that the execution runs inside of.
                int stat;      // exit status of child process.
                pid = fork();
                if (pid == -1)
                { //A problem has occured with the forking call.
                    perror("fork");
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
                       // cout << "hi";
                        didcommandexecute = false;
                    }
                }
            } //else
            //} // else2
            } //if doexecute = true
    
            //here we assign the truth values
            // i set this iteration of fr loop to not execute the command (only with && and || special cases)
            if (doexecute == false) {
            //   (  false && (?) ) is always false. (?) is never executed
            if (prevcon == "&&") {
                prevtruth = false;
            }
            //   (true || (?) ) is always true. (?) is never exeuted
            else if (prevcon == "||") {
                prevtruth = true;
            }
            }
            //doexecite = true, in this case there was an attempt to execute
            else {
            if (prevcon == "Start") {
               
                //if our command did execute properly
                if (didcommandexecute == true) {
                prevtruth = true;    
                }
                else {
                prevtruth = false;
                }
            }
            
            // (T && (?) )
            else if (prevcon == "&&") {
                //command executed properly
                // (true && true) = true
                if (didcommandexecute == true) {
                prevtruth = true;    
                }
                //comand did not execute properly
                // (true && false) = false
                else {
                prevtruth = false;
                }
            }
            //F || (?)
            else if (prevcon == "||") {
            
            //command executed properly
            //(false || true) = true
            if (didcommandexecute == true) {
                prevtruth = true;
            }
            // (false || false) = false
            else {
                prevtruth = false;
            }
            }
            else if (prevcon == ";") {
             //this is almost like starting from the start.
             prevtruth = true;   
            }
        
            
            }//bracket for else
            
         
                 
            //checking ( )
            if (inloop == true) {
                
                // if our ( occurs at the start of the parsed string or if it is the very first element in the ()
                if (Parsedlist.at(z)->start == true ) {
                
                if (prevtruth == true) {
                looptruth = true;
                }
                else {
                looptruth = false;
                }
                
                }
                
                else if (prevcon == "&&") {
                
                if (looptruth == true) {
                    // (T && T) = T
                    if (prevtruth == true) {
                        looptruth = true;
                    }
                    // (T && F) = F
                    else {
                        looptruth = false;
                    }
                }
                //looptruth == false
                else {
                    // (F && T) = F
                    if (prevtruth == true) {
                        looptruth = false;
                    }
                    // (F && F) = F
                    else {
                        looptruth = false;
                    }
                }
                    
                }
                
                else if (prevcon == "||") {
                    
                if (looptruth == true) {
                    // (T || F) = T
                    looptruth = true;
                }    
                    // (F || T) or (F || F)
                else {
                 if (prevtruth == true) {
                     looptruth = true;
                 }
                 else {
                     looptruth = false;
                 }
                }    
                    
                }
                
                else if (prevcon == ";") {
                // (echo hello; echo hi) = T    
                if (prevtruth == true) {
                    looptruth = true;
                }   
                // (echo hello; ech hi) = F
                else {
                    looptruth = false;
                }
    
                }
                
            }
            
               //assign prevcon here so we know it for the next loop
            //truth values and connectors reset if we reach a ;
            
            if (Parsedlist.at(z)->end == true) {
            prevtruth = looptruth;
            inloop = false;
            }
           
            prevcon = Parsedlist.at(z)->connector;
           
              
            
        delete[] anum;
        delete[] xnum;
        }// for int z
  
    }
};

#endif
