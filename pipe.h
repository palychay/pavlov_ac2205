#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

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
    void editpipe();
    
    static bool is_empty_pipe();

    friend std::ostream& operator << (std::ostream& out, const Pipe &p);
    friend std::ofstream& operator << (std::ofstream& fout, const Pipe &p);
    friend std::ifstream& operator >> (std::ifstream& fin, Pipe &p);
};
