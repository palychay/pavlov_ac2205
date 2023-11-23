#include "friendclass.h"
#include "correct_input.h"

bool PipeAndKC::is_empty_file(const string &s){
    ifstream file(s);
    return (!file || file.peek() == ifstream::traits_type::eof());
}

void PipeAndKC::load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap){
    string flnm;
    cout << "input: ";
    INPUT_LINE(cin, flnm);
    ifstream fin(flnm);
    if (!(fin)){
        cout << "no file\n";
        return;
    }
    Pipe::MaxID = 0;
    KC::MaxID = 0;
    fin >> Pipe::MaxID >> KC::MaxID;
    
    string s;
    while (getline(fin, s))
    {
        if(s == "here_kc"){
            KC kc;
            fin >> kc;
            kcmap[kc.getID()] = kc;}      
        else if(s == "here_pipe"){
            Pipe p;
            fin >> p;
            pmap[p.getID()] = p;}
    } 
}

void PipeAndKC::save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap){
    if (pmap.size() == 0 and kcmap.size() == 0){
        cout << "No data to save\n";
        return;
    } 
    string file;
    cout << "input: ";
    INPUT_LINE(cin, file); 
    while (!is_empty_file(file))
    {
        cout << "The file is not empty. Are you sure you want to overwrite the data?(yes/no): ";
        string s;
        INPUT_LINE(cin, s);
        if (s == "yes")
            break;
        cout << "input: ";
        INPUT_LINE(cin, file);

    }
    ofstream fout(file);
    fout << Pipe::MaxID << endl << KC::MaxID << endl;
            for (auto& [id, p] : pmap)
                fout << p;
            for (auto& [id, kc] : kcmap)
                fout << kc;
    fout.close();
}

void PipeAndKC::create_rebro(const unordered_map <int, KC>& kcmap, unordered_map <int, Pipe>& pmap, unordered_map <int, svyaz>& rebra){
    svyaz r;
    cout << "input id kc vhoda:";
    int idkcvh = get_correct(1000, 1);
    int m = 0;
    for (auto& [id, kc] : kcmap){
            if (id == idkcvh){
                r.vhod = idkcvh;
                m++;
            }  
        }
    if (m == 0)
        return;
    cout << "input id kc vihoda:";
    int idkcvih = get_correct(1000, 1);
    m = 0;
    for (auto& [id, kc] : kcmap){
            if (id == idkcvih){
                r.vihod = idkcvih;
                m++;
            }
        }
    if (m == 0)
        return;
    cout << "diametr of pipe(500, 700, 1000, 1400):";
    int di = Pipe::diametr_pipe();
    m = 0;
    for (auto& [id, p] : pmap){
            if (p.diametr == di and !(rebra.count(di))){
                rebra[p.getID()] = r;
                m++;
            }
    }
    if (m == 0) {
        Pipe p;
        p.new_pipe();
        pmap[p.getID()] = p;
        rebra.insert(pair<int, svyaz>(p.getID(), r));
        }  
}

