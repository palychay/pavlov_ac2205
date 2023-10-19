#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "correct_input.h"
#include "pipe.h"

using namespace std;


void editpipe(Pipe &p){
    cout << "a sign in repair(0 - no or 1 - yes): ";
    p.remont = get_correct(true, false);
    cout << endl;
}


struct KC // компрессорная станция
{
    string name;
    int kolich_ceh;
    int kolich_ceh_v_rabote;
    double effectivnost;
};

KC New_KC(){        //vvod new kc
    KC kc;
    cout << "new КС\n";
    cout << "name: ";
    cin >> ws;
    getline(cin, kc.name);
    cout << "number of workshops: ";
    kc.kolich_ceh = get_correct(1500, 0);
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    kc.kolich_ceh_v_rabote = get_correct(kc.kolich_ceh, 0);
    cout << "Efficiency input(from 0 to 1, including all numbers between them): ";
    kc.effectivnost = get_correct(1., 0.);
    cout << endl;
    return kc;
}

void Print_KC(const KC &kc){   //output new kc
    cout << "your kc\n";
    cout << "name kc: ";
    cout << kc.name << endl;
    cout << "Number of workshops: ";
    cout << kc.kolich_ceh << endl;
    cout << "Number of workshops in operation: ";
    cout << kc.kolich_ceh_v_rabote << endl;
    cout << "kc efficiency: ";
    cout << kc.effectivnost << endl;
    cout << endl;
}

void editkc(KC &kc){
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    kc.kolich_ceh_v_rabote = get_correct(kc.kolich_ceh, 0);
    cout << endl;
}


bool is_empty_pipe(const Pipe &p){
    if (p.diametr == -1){
        return true;
    }
    else{
        return false;
    }
}

bool is_empty_kc(const KC &kc){
    if (kc.kolich_ceh == -1){
        return true;
    }
    else{
        return false;
    }
}

bool is_empty_file(){
    ifstream file("data.txt");
    return (!file || file.peek() == ifstream::traits_type::eof());
}


ofstream& operator << (ofstream &fout, const Pipe &p){
    fout << "here_pipe\n" << p.kilometr_name << endl <<
     p.length << endl << p.diametr << endl << p.remont << endl;
    return fout;
}

ofstream& operator << (ofstream &fout, const KC &kc){
    fout << "here_kc\n" << kc.name << endl << kc.kolich_ceh << endl
     << kc.kolich_ceh_v_rabote << endl << kc.effectivnost << endl;
    return fout;
}
        
void save_data(const Pipe &p, const KC &kc)
{   
    if (is_empty_pipe(p) && is_empty_kc(kc)){
        cout << "No data to save\n";
        return;
    }
    if (!is_empty_file())
    {
        cout << "The file is not empty. Are you sure you want to overwrite the data?(yes/no): ";
        string s;
        cin >> s;//!
        if (s == "no")
        {
            cout << "Select another file to save\n";
            return;
        }
    }
    ofstream fout("data.txt");
    if (!is_empty_pipe(p))
        fout << p;
    if (!is_empty_kc(kc))
        fout << kc;
    fout.close();
}



ifstream& operator >> (ifstream &fin, Pipe &p){
    fin>>ws;
    getline(fin, p.kilometr_name);
    fin >> p.length >> p.diametr >> p.remont;
    return fin;
}

ifstream& operator >> (ifstream &fin, KC &kc){
    fin>>ws;
    getline(fin, kc.name);
    fin >> kc.kolich_ceh >> kc.kolich_ceh_v_rabote >> kc.effectivnost;
    return fin;
}


void load_data(Pipe &p, KC &kc){
    if (is_empty_file()){
        cout << "no data\n";
        return;
    }

    ifstream fin("data.txt");
    string s;
    while (getline(fin, s))
    {
        if(s == "here_kc")
            fin >> kc;        
        else if(s == "here_pipe")
            fin >> p ;
    }
}


int Menu(){
    Pipe p;
    p.diametr = -1;
    KC kc;
    kc.kolich_ceh = -1;
    while (true){
        cout << "menu\n";
        cout << " 1. add pipe\n";
        cout << " 2. add kc\n";
        cout << " 3. Viewing available objects\n";
        cout << " 4. edit pipe\n";
        cout << " 5. edit kc\n";
        cout << " 6. save\n";
        cout << " 7. to load\n";
        cout << " 8. exit\n";
        cout << endl;
        int choice;//!!!
        cout << "Please choose a number from 1 to 8: ";
        choice = get_correct(8, 1);
        cout << endl;
        switch (choice)
        {
        case 1:
            p.new_pipe();
            break;

        case 2:
            kc = New_KC();
            break;

        case 3:
            if (is_empty_pipe(p) == false && is_empty_kc(kc) == true){
                p.Print_Pipe();
                cout << "kc - no!\n" << endl;
            }
            else if (is_empty_pipe(p) == true && is_empty_kc(kc) == false){
                Print_KC(kc);
                cout << "pipe - no!\n" << endl;
            }
            else if (is_empty_pipe(p) == true && is_empty_kc(kc) == true){
                cout << "objects no!\n" << endl;
            }
            else{
                p.Print_Pipe();
                Print_KC(kc);
            }
            break;

        case 4:
            if (!(is_empty_pipe(p))){
                editpipe(p);
            }
            else{
                cout << "There is no such object\n" << endl;
            }
            break;

        case 5:
            if (!(is_empty_kc(kc))){
                editkc(kc);
            }
            else{
                cout << "There is no such object\n" << endl;
            }
            break;

        case 6:
            save_data(p, kc);
            break;

        case 7:
            load_data(p, kc);
            break;

        case 8:
            return 0;

        default:
            break;
        }
    }
}


int main(){
    Menu();
    return 0;
}