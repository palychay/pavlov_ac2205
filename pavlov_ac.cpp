#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "correct_input.h"
#include "pipe.h"
#include "kc.h"

using namespace std;


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
    if (p.is_empty_pipe() && kc.is_empty_kc()){
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
    if (!p.is_empty_pipe())
        fout << p;
    if (!kc.is_empty_kc())
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


void text_menu(){
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
}

int Menu(){
    Pipe p;
    p.diametr = -1;
    KC kc;
    kc.kolich_ceh = -1;
    while (true){
        text_menu();
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
            kc.new_kc();
            break;

        case 3:
            if (p.is_empty_pipe() == false && kc.is_empty_kc() == true){
                p.Print_Pipe();
                cout << "kc - no!\n" << endl;
            }
            else if (p.is_empty_pipe() == true && kc.is_empty_kc() == false){
                kc.Print_KC();
                cout << "pipe - no!\n" << endl;
            }
            else if (p.is_empty_pipe() == true && kc.is_empty_kc() == true){
                cout << "objects no!\n" << endl;
            }
            else{
                p.Print_Pipe();
                kc.Print_KC();
            }
            break;

        case 4:
            if (!(p.is_empty_pipe())){
                p.editpipe();
            }
            else{
                cout << "There is no such object\n" << endl;
            }
            break;

        case 5:
            if (!(kc.is_empty_kc())){
                kc.editkc();
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