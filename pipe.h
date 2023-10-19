#include <iostream>
#include <string>


using namespace std;

class Pipe  // труба
{   
    public:
    string kilometr_name;
    double length;
    int diametr;
    bool remont;

    void new_pipe();
    void Print_Pipe() const;
    void editpipe();
    bool is_empty_pipe() const;

    
};
