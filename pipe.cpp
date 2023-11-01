#include "pipe.h"
#include "correct_input.h"

int Pipe::MaxID = 0;

ostream& operator << (ostream &out, const Pipe &p){
    out << "pipe name: " << p.kilometr_name  << "\t" << "length: " << p.length << "\t"
    << "pipe diametr: " << p.diametr << "\t"
    << "pipe is remont: " << p.remont << endl;
    return out;
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

void Pipe::Print_Pipe() const
{
    cout << "Your pipe:\n";
        cout << "Kilometer mark: ";
        cout << kilometr_name << endl;
        cout << "Length (in kilometers): ";
        cout << length << endl;
        cout << "Pipe diameter (in millimeters): ";
        cout << diametr << endl;
        cout << "A sign in repair(0 - no, 1 - yes): ";
        cout << remont << endl;
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
