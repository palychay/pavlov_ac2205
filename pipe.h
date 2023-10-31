#include <iostream>
#include <string>


using namespace std;

class Pipe  // труба
{   
private:
    static int MaxID;
    int id;

    string kilometr_name;
    double length;
    int diametr = -1;
    bool remont;

public:
    void new_pipe();
    void Print_Pipe() const;
    void editpipe();
    bool is_empty_pipe() const;
    int getID() const;
    bool getrepair();

    friend std::ostream& operator << (std::ostream& out, const Pipe &p);
};
