#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "correct_input.h"
#include "pipe.h"
#include "kc.h"
#include <unordered_map>


using namespace std;



bool is_empty_file(){
    ifstream file("data.txt");
    return (!file || file.peek() == ifstream::traits_type::eof());
}
/*
ofstream& operator << (ofstream &fout, const Pipe &p){
    fout << "here_pipe\n" << p.kilometr_name << endl <<
     p.length << endl << p.diametr << endl << p.remont << endl;
    return fout;
}
*/
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

/*
ifstream& operator >> (ifstream &fin, Pipe &p){
    fin>>ws;
    getline(fin, p.kilometr_name);
    fin >> p.length >> p.diametr >> p.remont;
    return fin;
}
*/
ifstream& operator >> (ifstream &fin, KC &kc){
    fin>>ws;
    getline(fin, kc.name);
    fin >> kc.kolich_ceh >> kc.kolich_ceh_v_rabote >> kc.effectivnost;
    return fin;
}
/*
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
*/
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

void out_kcmap(unordered_map <int, KC> &kcmap){
    for (const auto& [id, kc] : kcmap){
        cout << "id: " << id << "\t" << kc;
    }
}

void out_pmap(unordered_map <int, Pipe> &pmap){
    for (const auto& [id, p] : pmap){
        cout << "id: " << id << "\t" << p;
    }
}


int Menu(){
    
    unordered_map <int, KC> kcmap;
    unordered_map <int, Pipe> pmap;
    Pipe p;
    KC kc;
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
            pmap[p.getID()] = p;
            break;

        case 2:
            kc.add_new_kc();
            kcmap[kc.id] = kc;
            break;

        case 3:
            if (p.is_empty_pipe() == false && kc.is_empty_kc() == true){
                cout << "Yours pipes:\n";
                out_pmap(pmap);
                cout << "kc - no!\n" << endl;
                cout << endl;
            }
            else if (p.is_empty_pipe() == true && kc.is_empty_kc() == false){
                cout << "Yours kcs:\n";
                out_kcmap(kcmap);
                cout << "pipe - no!\n" << endl;
                cout << endl;
            }
            else if (p.is_empty_pipe() == true && kc.is_empty_kc() == true){
                cout << "objects no!\n" << endl;
            }
            else{
                cout << "Yours pipes:\n";
                out_pmap(pmap);
                cout << endl;
                cout << "Yours kcs:\n";
                out_kcmap(kcmap);
                cout << endl;
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
                kc.editkc(kcmap);
            }
            else{
                cout << "There is no such object\n" << endl;
            }
            break;

        case 6:
            save_data(p, kc);
            break;

        case 7:
            /*load_data(p, kc);*/
            break;

        case 8:
            return 0;

        default:
            break;
        }
    }
}


int main(){
    redirect_output_wrapper cerr_out(cerr);
	ofstream logfile("log_");
	if (logfile)
		cerr_out.redirect(logfile);
    Menu();
    return 0;
}