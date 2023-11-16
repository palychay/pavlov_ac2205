#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class KC{
private:
    int id;
    static int MaxID;
    /*основные параметры станции*/
    string name;
    int kolich_ceh;
    int kolich_ceh_v_rabote;
    double effectivnost;

public:

    int getID() const;
    string getname() const;
    bool geteffectivnost() const;
    int get_kcehov() const;
    void set_wcehov(int w);
    /*основные действия над станциями*/
    void add_new_kc();
    double getLoad() const;

    friend class PipeAndKC;

    friend std::ofstream& operator << (std::ofstream& fout, const KC &kc);
    friend std::ostream& operator << (std::ostream& out, const KC &kc);
    friend std::ifstream& operator >> (std::ifstream& fin, KC &kc);
};