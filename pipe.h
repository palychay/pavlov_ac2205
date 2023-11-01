#include <iostream>
#include <string>
#include <unordered_map>

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
    int getID() const;
    string getKmname() const;
    bool getRepair() const;

    void new_pipe();
    void Print_Pipe() const;
    void editpipe();
    void delpipe(unordered_map <int, Pipe> &pmap, int &key);

    bool is_empty_pipe() const;

    

    friend std::ostream& operator << (std::ostream& out, const Pipe &p);
};
