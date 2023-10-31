#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class KC{
    
public:
    static int MaxID;
    int id;
    /*основные параметры станции*/
    string name;
    int kolich_ceh = -1;
    int kolich_ceh_v_rabote;
    double effectivnost;

    /*основные действия над станциями*/
    void add_new_kc();
    void editkc(unordered_map <int, KC> &kcmap);
    void delete_kc(unordered_map <int, KC> &kcmap, int &kc);


    bool is_empty_kc() const;

    friend std::ostream& operator << (std::ostream& out, const KC &kc);
};