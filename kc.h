#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class KC{
    
public:
    static int MaxID;
    int id;
    string name;
    int kolich_ceh = -1;
    int kolich_ceh_v_rabote;
    double effectivnost;

    void add_new_kc();
    void editkc(unordered_map <int, KC> &kcmap);
    bool is_empty_kc() const;
    void filter_by_name(unordered_map <int, KC> &kcmap);
    void delete_kc();
    
    friend std::ostream& operator << (std::ostream& out, const KC &kc);
};