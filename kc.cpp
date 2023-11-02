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

ofstream& operator << (ofstream &fout, const KC &kc){
    fout << "here_kc\n" << kc.id << endl << kc.name << endl << kc.kolich_ceh << endl
     << kc.kolich_ceh_v_rabote << endl << kc.effectivnost << endl;
    return fout;
}

ifstream& operator >> (ifstream &fin, KC &kc){
    fin >> kc.id;
    fin>>ws;
    getline(fin, kc.name);
    fin >> kc.kolich_ceh >> kc.kolich_ceh_v_rabote >> kc.effectivnost;
    return fin;
}

void KC::add_new_kc(){
    id = ++MaxID;
    cout << "new kc\n";
    cout << "name: ";
    cin >> ws;
    getline(cin, name);
    cerr << name << endl;
    cout << "number of workshops: ";
    kolich_ceh = get_correct(1500, 0);
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    kolich_ceh_v_rabote = get_correct(kolich_ceh, 0);
    effectivnost = (double (kolich_ceh_v_rabote) / double(kolich_ceh)) * 100;
    cout << endl;
}

void KC::editkc(int &wceh){
    effectivnost = (double(wceh) / double(kolich_ceh)) * 100;       
}
    
bool KC::is_empty_kc() const{
    if (MaxID == 0){
        return true;
    }
    else{
        return false;
    }
}

int KC::getID() const{
    return id;
}

string KC::getname() const{
    return name;
}

bool KC::geteffectivnost() const{
    return effectivnost;
}

int KC::get_kcehov() const{
    return kolich_ceh;
}

void KC::set_wcehov(int &w){
    kolich_ceh_v_rabote = w;
}