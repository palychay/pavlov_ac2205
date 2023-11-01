#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Pipe  // труба
{   
private:
    int id;

    string kilometr_name;
    double length;
    int diametr = -1;
    bool remont;

public:
    static int MaxID;
    
    int getID() const;
    string getKmname() const;
    bool getRepair() const;


    void new_pipe();
    void Print_Pipe() const;
    void editpipe();
    

    bool is_empty_pipe() const;

    

    friend std::ostream& operator << (std::ostream& out, const Pipe &p);
};
