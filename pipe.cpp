#include "pipe.h"
#include "correct_input.h"

int Pipe::MaxID = 0;

ostream& operator << (ostream &out, const Pipe &p){
    out << "pipe name: " << p.kilometr_name  << "\t" << "length: " << p.length << "\t"
    << "pipe diametr: " << p.diametr << "\t"
    << "pipe is remont: " << p.remont << endl;
    return out;
}

ofstream& operator << (ofstream &fout, const Pipe &p){
    fout << "here_pipe\n" << p.id << endl << p.kilometr_name << endl <<
     p.length << endl << p.diametr << endl << p.remont << endl;
    return fout;
}

ifstream& operator >> (ifstream &fin, Pipe &p){
    fin >> p.id;
    fin>>ws;
    getline(fin, p.kilometr_name);
    fin >> p.length >> p.diametr >> p.remont;
    return fin;
}

void Pipe::new_pipe()
{
    id = ++MaxID;
    cout << "New pipe\n";
    cout << "Kilometer mark: ";
    cin >> ws;
    getline(cin, kilometr_name);
    cout << "Length(km): ";
    length = get_correct(1500., 0.);
    cout << "Pipe Diameter(mm): ";
    diametr = get_correct(1500, 0);
    cout << "Sign in repair(0 - no or 1 - yes): ";
    remont = get_correct(true, false);
    cout << endl;
}

void Pipe::editpipe(){
    remont = !remont;
    cout << endl;
}

bool Pipe::is_empty_pipe() const{
    if (MaxID == 0){
        return true;
    }
    else{
        return false;
    }
}

int Pipe::getID() const{
    return id;
}

string Pipe::getKmname() const{
    return kilometr_name;
}

bool Pipe::getRepair() const{
    return remont;
}
