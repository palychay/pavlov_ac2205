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

template<typename T>
using Filter = bool(*)(const Pipe &p, T parametr);

bool CheckByName(const Pipe &p, string parametr)
{
    return p.getKmname().find(parametr) != std::string::npos;
}
bool CheckByRepair(const Pipe &p, bool parametr)
{
	return p.getRepair() == parametr;
}

template<typename T>
unordered_map <int, Pipe> FindPipesByFilter(const unordered_map<int, Pipe>& pmap, Filter<T> f, T parametr)
{
	unordered_map <int, Pipe> result;
    for (const auto& [id, p] : pmap){
        if (f(p, parametr)){
            result[id] = p;
        }
    }

	return result;
}
/*
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

/*
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

void editAllpipe(unordered_map <int, Pipe> &pmap){
     for (auto& [id, p] : pmap){
        p.editpipe();
     }
}

void editPipe_byname(unordered_map <int, Pipe> &pmap, string &s){
    for (auto& [id, p] : pmap){
        if (CheckByName(p, s)){
            p.editpipe();
        }
    }
}

void editPipe_byrepair(unordered_map <int, Pipe> &pmap, bool &b){
    for (auto& [id, p] : pmap){
        if (CheckByRepair(p, b)){
            p.editpipe();
        }
    }
}

void delallPipe(unordered_map <int, Pipe> &pmap){
    unordered_map <int, Pipe> newmap;
    pmap = newmap;
    Pipe::MaxID = 0;
}

void delPipe_byname(unordered_map <int, Pipe> &pmap, string &s){
    if (pmap.size() == 1){
        delallPipe(pmap);
    }
    else{
        int k = 0;
        for (auto& [id, p] : pmap){
            if (CheckByName(p, s)){
                k++;
            }
        }
        if (k == pmap.size()){
            delallPipe(pmap);
        }
        else{
            for (auto& [id, p] : pmap){
            if (CheckByName(p, s)){
                pmap.erase(id);
            }
        }
        }
    }
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
        int choice;
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
                cout << "Edit-0 or delete-1: ";
                int i;
                i = get_correct(1, 0);
                if (i == 0){
                    cout << "Edit all pipes-0 or by filter name-1 or by filter repair-2: ";
                    i = get_correct(2, 0);
                    if (i == 2){
                        cout << "repair(0 - no or 1 - yes): ";
                        bool b;
                        b = get_correct(1, 0);
                        editPipe_byrepair(pmap, b);
                    }
                    else if (i == 1){
                        cout << "name: ";
                        string s;
                        cin >> s;
                        editPipe_byname(pmap, s);
                    }
                    else{
                        editAllpipe(pmap);
                    }
                }
                else{
                    cout << "Delete all pipes-0 or by filter name-1: ";
                    i = get_correct(1, 0);
                    if (i == 1){
                        cout << "name: ";
                        string s;
                        cin >> s;
                        delPipe_byname(pmap, s);
                    }
                    else{
                        delallPipe(pmap);
                    }
                }
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
            //save_data(p, kc);
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