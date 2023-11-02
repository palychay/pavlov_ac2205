#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "correct_input.h"
#include "pipe.h"
#include "kc.h"
#include <unordered_map>


using namespace std;

bool is_empty_file(string &s){
    ifstream file(s);
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


template<typename T>
using Filter1 = bool(*)(const KC &kc, T parametr);

bool CheckByName(const KC &kc, string parametr)
{
    return kc.getname().find(parametr) != std::string::npos;
}
bool CheckByeffectivnost(const KC &kc, int parametr)
{
	return (100 - int(kc.geteffectivnost())) == parametr;
}

template<typename T>
unordered_map <int, KC> FindKCsByFilter(const unordered_map<int, KC>& kcmap, Filter1<T> f, T parametr)
{
	unordered_map <int, KC> result;
    for (const auto& [id, kc] : kcmap){
        if (f(kc, parametr)){
            result[id] = kc;
        }
    }

	return result;
}
     
void save_data(const Pipe &p, const KC &kc, string &file, unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap)
{   
    if (p.is_empty_pipe() && kc.is_empty_kc()){
        cout << "No data to save\n";
        return;
    }
    if (!is_empty_file(file))
    {
        cout << "The file is not empty. Are you sure you want to overwrite the data?(yes/no): ";
        string s;
        cin >> s;//!
        cerr << s << endl;
        if (s == "no")
        {
            cout << "Select another file to save: ";
            string newfile;
            cin >> newfile;
            cerr << newfile << endl;
            ofstream fout(newfile);
            fout << Pipe::MaxID << endl << KC::MaxID << endl;
            if (!p.is_empty_pipe())
                for (auto& [id, p] : pmap)
                    fout << p;
            if (!kc.is_empty_kc())
                for (auto& [id, kc] : kcmap)
                    fout << kc;
            fout.close();
            return;
        }
    }
    ofstream fout(file);
    fout << Pipe::MaxID << endl << KC::MaxID << endl;
    if (!p.is_empty_pipe())
            for (auto& [id, p] : pmap)
                fout << p;
    if (!kc.is_empty_kc())
            for (auto& [id, kc] : kcmap)
                fout << kc;
    fout.close();
}

void load_data(Pipe &p, KC &kc, string &flnm, unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap){
    
    if (is_empty_file(flnm)){
        cout << "no data\n";
        return;
    }
    
    ifstream fin(flnm);
    fin >> Pipe::MaxID >> KC::MaxID;
    string s;
    while (getline(fin, s))
    {
        if(s == "here_kc"){
            fin >> kc;
            kcmap[kc.getID()] = kc;}      
        else if(s == "here_pipe"){
            fin >> p;
            pmap[p.getID()] = p;}
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
            auto it = pmap.begin();
            while (it != pmap.end()) {
                if (CheckByName(it->second, s)) {
                    it = pmap.erase(it);
                    }
                else {
                    ++it;
                    }
}   
        }
    }
}

void out_pmap(unordered_map <int, Pipe> &pmap){
    for (const auto& [id, p] : pmap){
        cout << "id: " << id << "\t" << p;
    }
}

void out_kcmap(unordered_map <int, KC> &kcmap){
    for (const auto& [id, kc] : kcmap){
        cout << "id: " << id << "\t" << kc;
    }
}

void editKC_byname(unordered_map <int, KC> &kcmap){
    cout << "name: ";
    string s;
    cin >> s;
    cerr << s << endl;
    cout << "wceh: ";
    int wceh;
    for (auto& [id, kc] : kcmap){
        if (CheckByName(kc, s)){
            wceh = get_correct(kc.get_kcehov(), 0);
            kc.editkc(wceh);
            kc.set_wcehov(wceh);
        }
    }
}

void delKC_byname(unordered_map <int, KC> &kcmap){
    if (kcmap.size() == 1){
        unordered_map <int, KC> newmap;
        kcmap = newmap;
        KC::MaxID = 0;
    }
    else{
        int k = 0;
        cout << "name: ";
        string s;
        cin >> s;
        cerr << s << endl;
        for (auto& [id, kc] : kcmap){
            if (CheckByName(kc, s)){
                k++;
            }
        }
        if (k == kcmap.size()){
            unordered_map <int, KC> newmap;
            kcmap = newmap;
            KC::MaxID = 0;
        }
        else{
            auto it = kcmap.begin();
            while (it != kcmap.end()) {
                if (CheckByName(it->second, s)) {
                    it = kcmap.erase(it);
                    }
                else {
                    ++it;
                    }
        }
    }
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
            kcmap[kc.getID()] = kc;
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
                        cerr << s << endl;
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
                        cerr << s << endl;
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
                cout << "Edit-0 or delete-1: ";
                int i;
                i = get_correct(1, 0);
                if (i == 0){
                    editKC_byname(kcmap);
                    }
                else{
                    delKC_byname(kcmap);
                }
            }
            else{
                cout << "There is no such object\n" << endl;
            }
            break;

        case 6:
            {cout << "select save-file:";
            string file;
            cin >> file;
            cerr << file << endl;
            save_data(p, kc, file, pmap, kcmap);}
            break;

        case 7:
            {
                string flnm;
                cout << "input: ";
                cin >> flnm;
                cerr << flnm << endl;
                load_data(p, kc, flnm, pmap, kcmap);
            }
            /*load_data(p, kc,);*/
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