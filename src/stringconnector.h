#ifndef stringconnector_H
#define stringconnector_H


class stringconnector {
    private:
    
    
    
    public:
    
    bool start;
    bool mid;
    bool end;
    
    
    string connector;
    string executable;
    string argument;
    
    //special constructor for the ; case
    stringconnector(string a, string c) {
        start = false;
        mid = false;
        end = false;
        executable = a;
        connector = c;
        argument = "";
    }
    
    void specialpushback(string b) {
        argument.append(b);
    }
    
    void pushback(string a) {
        argument.append(" ");
        argument.append(a);
    }
    
    void output(int u) {
        cout << "Executable" << u << ": " << executable << endl;
        cout << "Argument" << u <<   ": " << argument << endl;
        cout << "Connector" << u << ": " << connector << endl;
    }
    
    int getsize() {
        return argument.size();
    }
    
    
    
};



#endif
