#include "pipe.h"
#include "correct_input.h"

void Pipe::new_pipe()
{
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
    cout << "a sign in repair(0 - no or 1 - yes): ";
    remont = get_correct(true, false);
    cout << endl;
}

bool Pipe::is_empty_pipe() const{
    if (diametr == -1){
        return true;
    }
    else{
        return false;
    }
}

