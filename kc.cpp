#include "kc.h"
#include "correct_input.h"

int KC::MaxID = 0;

ostream& operator << (ostream &out, const KC &kc){
    out << "kc name:" << kc.name << "\t"
    << "kolich ceh:" << kc.kolich_ceh << "\t"
    << "kolich_ceh_v_rabote:" << kc.kolich_ceh_v_rabote << "\t"
    << "effectivnost:" << kc.effectivnost << endl;
    return out;
}


void KC::add_new_kc(){
    id = ++MaxID;
    cout << "new kc\n";
    cout << "name: ";
    cin >> ws;
    getline(cin, name);
    cout << "number of workshops: ";
    kolich_ceh = get_correct(1500, 0);
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    kolich_ceh_v_rabote = get_correct(kolich_ceh, 0);
    effectivnost = (double (kolich_ceh_v_rabote) / double(kolich_ceh)) * 100;
    cout << endl;
}

void KC::editkc(unordered_map <int, KC> &kcmap){
    int cehi;
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    cehi = get_correct(kolich_ceh, 0);
        for (auto& [id, kc] : kcmap){
            if (kc.kolich_ceh > cehi){
                kc.kolich_ceh_v_rabote = cehi;
            }
            kc.effectivnost = (double (kc.kolich_ceh_v_rabote) / double(kc.kolich_ceh)) * 100;
        }
}
    
bool KC::is_empty_kc() const{
    if (MaxID == 0){
        return true;
    }
    else{
        return false;
    }
}

void KC::delete_kc(unordered_map <int, KC> &kcmap, int &key){
    kcmap.erase(key);
}