#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Pipe  // труба
{   
private:
    int id;
    static int MaxID;
    string kilometr_name;
    double length;
    int diametr = -1;
    bool remont;

public:
    int getID() const;
    static int getMaxID(){return MaxID;};
    string getKmname() const;
    bool getRepair() const;

    void new_pipe();
    void editpipe();
    
    static void setMaxId(int &pid){MaxID = pid;};

    friend std::ostream& operator << (std::ostream& out, const Pipe &p);
    friend std::ofstream& operator << (std::ofstream& fout, const Pipe &p);
    friend std::ifstream& operator >> (std::ifstream& fin, Pipe &p);
};
