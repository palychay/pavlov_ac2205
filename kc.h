#include <iostream>
#include <string>

using namespace std;

class KC{
    public:
    string name;
    int kolich_ceh;
    int kolich_ceh_v_rabote;
    double effectivnost;

    void new_kc();
    void Print_KC() const;
    void editkc();
    bool is_empty_kc() const;
};