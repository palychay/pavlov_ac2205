#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "correct_input.h"

#include <unordered_map>
#include <chrono>
#include <format>
#include "friendclass.h"

using namespace std;
using namespace chrono;


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
unordered_set <int> FindPipesByFilter(const unordered_map<int, Pipe>& pmap, Filter<T> f, T parametr)
{
	unordered_set <int> result;
    for (const auto& [id, p] : pmap){
        if (f(p, parametr)){
            result.insert(id);
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
bool CheckByLoad(const KC &kc, int parametr)
{
	return (100 - int(kc.getLoad())) == parametr;
}

template<typename T>
unordered_set <int> FindKCsByFilter(const unordered_map<int, KC>& kcmap, Filter1<T> f, T parametr)
{
	unordered_set <int> result;
    for (const auto& [id, kc] : kcmap){
        if (f(kc, parametr)){
            result.insert(id);
        }
    }
	return result;
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
    cout << " 8. create a network\n";
    cout << " 9. exit\n";
    cout << endl;
}

void choiceEdit(unordered_map<int, Pipe>& pmap, const unordered_set <int>& f){
    int sk = f.size();
    if (sk){
        unordered_set <int> yourchoice;
        cout << "choice id for edit, '0' if you want end input:";
        int ssze = get_correct(1000, 0);
        
        while (ssze){
            if (f.count(ssze)){
                yourchoice.insert(ssze);
            }
            ssze = get_correct(1000, 0);
        }
        for (auto& [id, p] : pmap){
            if (yourchoice.count(id)){
                p.editpipe();
            }
        }
    }
    else
        return;
}


void editAllpipe(unordered_map <int, Pipe> &pmap){
     for (auto& [id, p] : pmap){
        p.editpipe();
     }
}

void editPipe_byname(unordered_map <int, Pipe> &pmap){
    cout << "input: ";
    string s;
    INPUT_LINE(cin, s);
    for (int t: FindPipesByFilter(pmap, CheckByName, s)){
        cout << "id: " << t << endl;
    }
    choiceEdit(pmap, FindPipesByFilter(pmap, CheckByName, s));
}

void editPipe_byrepair(unordered_map <int, Pipe> &pmap){
    cout << "repair(0 - no or 1 - yes): ";
    bool b;
    b = get_correct(1, 0);
    for (int t: FindPipesByFilter(pmap, CheckByRepair, b)){
        cout << "id: " << t << endl;
    }
    choiceEdit(pmap, FindPipesByFilter(pmap, CheckByRepair, b));
}

void editPipeINcase4(unordered_map <int, Pipe> &pmap){
    cout << "Edit all pipes-0 or by filter name-1 or by filter repair-2: ";
    int j;
    j = get_correct(2, 0);
    if (j == 2){
        editPipe_byrepair(pmap);
        }
    else if (j == 1){
        editPipe_byname(pmap);
        }
    else{
        editAllpipe(pmap);
        }
}

void choiceDel(unordered_map<int, Pipe>& pmap, const unordered_set <int>& f){
    int sk = f.size();
    if (sk) {
        unordered_set <int> yourchoice;
        cout << "choice id for delete:";
        int ssze = get_correct(1000, 0);
        while (ssze){
            if (f.count(ssze)){
                yourchoice.insert(ssze);
            }
            ssze = get_correct(1000, 0);
        }
        for (int x: yourchoice){
            pmap.erase(x);
        }
    }
    else
        return;
}

void delallPipe(unordered_map <int, Pipe> &pmap){
    pmap.clear();
}

void delPipe_byname(unordered_map <int, Pipe> &pmap){
    cout << "name: ";
    string s;
    INPUT_LINE(cin, s);
    for (int t: FindPipesByFilter(pmap, CheckByName, s)){
        cout << "id: " << t << endl;
    }
    choiceDel(pmap, FindPipesByFilter(pmap, CheckByName, s));
}

void delPipeINcase4(unordered_map <int, Pipe> &pmap){
    cout << "Delete all pipes-0 or by filter name-1: ";
    int l;
    l = get_correct(1, 0);
    if (l == 1){
        delPipe_byname(pmap);
    }
    else{
        delallPipe(pmap);
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

void choiceEdit(unordered_map<int, KC>& kcmap, const unordered_set <int>& f){
    int sk = f.size();
    if (sk){
        unordered_set <int> yourchoice;
        cout << "choice id for edit:\n";
        int ssze = get_correct(1000, 0);
        while (ssze){
            if (f.count(ssze)){
                yourchoice.insert(ssze);
            }
            ssze = get_correct(1000, 0);
        }
        int wceh;
        for (auto& [id, kc] : kcmap){
            if (yourchoice.count(id)){
                cout << "wceh: ";
                wceh = get_correct(kc.get_kcehov(), 0);
                kc.set_wcehov(wceh);
            }
        }
    }
    else
        return;
}

void editKC_byname(unordered_map <int, KC> &kcmap){
    cout << "name: ";
    string s;
    INPUT_LINE(cin, s);
    for (int t: FindKCsByFilter(kcmap, CheckByName, s)){
        cout << "id: " << t << endl;
    }
    choiceEdit(kcmap, FindKCsByFilter(kcmap, CheckByName, s));
}

void choiceDel(unordered_map<int, KC>& kcmap, const unordered_set <int>& f){
    int sk = f.size();
    if (sk) {
        unordered_set <int> yourchoice;
        cout << "choice id for edit:\n";
        int ssze = get_correct(1000, 0);
        while (ssze){
            if (f.count(ssze)){
                yourchoice.insert(ssze);
            }
            ssze = get_correct(1000, 0);
        }
        for (int x: yourchoice){
            kcmap.erase(x);
        }
    }
    else
        return;
}

void delKC_byname(unordered_map <int, KC> &kcmap){
    cout << "name: ";
    string s;
    INPUT_LINE(cin, s);
    for (int t: FindKCsByFilter(kcmap, CheckByName, s)){
        cout << "id: " << t << endl;
    }
    choiceDel(kcmap, FindKCsByFilter(kcmap, CheckByName, s));    
}

int Menu(){
    unordered_map <int, KC> kcmap;
    unordered_map <int, Pipe> pmap;
    unordered_map <int, PipeAndKC::svyaz> rebra;
    while (true){
        text_menu();
        int choice;
        cout << "Please choose a number from 1 to 9: ";
        choice = get_correct(9, 1);
        cout << endl;
        switch (choice)
        {
        case 1:
        {
            Pipe p;
            p.new_pipe();
            pmap[p.getID()] = p;
            break;
        }

        case 2:
        {
            KC kc;
            kc.add_new_kc();
            kcmap[kc.getID()] = kc;
            break;
        }
        case 3:
            if (pmap.size() != 0 && kcmap.size() == 0){
                cout << "Yours pipes:\n";
                out_pmap(pmap);
                cout << "kc - no!\n" << endl;
                cout << endl;
            }
            else if (pmap.size() == 0 && kcmap.size() != 0){
                cout << "Yours kcs:\n";
                out_kcmap(kcmap);
                cout << "pipe - no!\n" << endl;
                cout << endl;
            }
            else if (pmap.size() == 0 && kcmap.size() == 0){
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
            if (pmap.size() != 0){
                cout << "Edit-0 or delete-1: ";
                int i;
                i = get_correct(1, 0);
                if (i == 0){
                    editPipeINcase4(pmap);
                }
                else{
                    delPipeINcase4(pmap);
                }
            }
            else{
                cout << "There is no such object\n" << endl;
            }
            break;

        case 5:
            if (kcmap.size() != 0){
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
            PipeAndKC pkc;
            pkc.save_data(pmap, kcmap);
            break;

        case 7:
            pkc.load_data(pmap, kcmap);
            break;

        case 8:
            {
            pkc.create_rebro(kcmap, pmap, rebra);
            cout << rebra.size() << endl;
            break;}

        case 9:
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