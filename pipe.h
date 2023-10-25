#include <iostream>
#include <string>


using namespace std;

class Pipe  // труба
{   
    public:
    static int MaxID;
    int id;

    string kilometr_name;
    double length;
    int diametr = -1;
    bool remont;

    void new_pipe();
    void Print_Pipe() const;
    void editpipe();
    bool is_empty_pipe() const;

    friend std::ostream& operator << (std::ostream& out, const Pipe &p);
};
