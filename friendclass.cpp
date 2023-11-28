#include "friendclass.h"
#include "correct_input.h"


ostream& operator << (ostream &out, const PipeAndKC::svyaz &r){
    out << "id vh: " << r.vhod << " " << "id vihod: " << r.vihod << " ";
    return out;
}

ofstream& operator << (ofstream &fout, const unordered_map<int, PipeAndKC::svyaz> &rebra){
    fout << "here_rebra\n";
    for (auto& [id, r] : rebra){
        fout << id << endl << r.vhod << endl << r.vihod << endl;
    }
    return fout;
}
/*
ifstream& operator >> (ifstream &fin, unordered_map<int, svyaz>& rebra){
    int idp, vh, vih;
    fin >> idp >> vh >> vih;
    PipeAndKC::svyaz r;
    r.vhod = vh;
    r.vihod = vih;
    rebra[idp] = r;
    return fin;*/

void PipeAndKC::see_rebra(const unordered_map <int, svyaz>& rebra){
    for (auto& [id, r] : rebra){
        cout << r << "id pipe: " << id << endl;
    }
}

bool PipeAndKC::is_empty_file(const string &s){
    ifstream file(s);
    return (!file || file.peek() == ifstream::traits_type::eof());
}

void PipeAndKC::load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap, unordered_map <int, svyaz>& rebra){
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
            
        else if(s == "here_rebra"){
            int idp, vh, vih;
            fin >> idp >> vh >> vih;
            svyaz r;
            r.vhod = vh;
            r.vihod = vih;
            rebra[idp] = r;
        }
    } 
}

void PipeAndKC::save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap, const unordered_map <int, svyaz>& rebra){
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
            fout << rebra;
    fout.close();
}

void PipeAndKC::create_rebro(const unordered_map <int, KC>& kcmap, unordered_map <int, Pipe>& pmap, unordered_map <int, svyaz>& rebra){
    svyaz r;
    cout << "input id kc vhoda:";
    int idkcvh = get_correct(1000, 1);
    auto it = kcmap.find(idkcvh);
    if (it != kcmap.end()) {
        r.vhod = idkcvh;
    }
    else
        return;
    cout << "input id kc vihoda:";
    int idkcvih = get_correct(1000, 1);
    it = kcmap.find(idkcvih);
    if (it != kcmap.end() && r.vhod != idkcvih) {
        r.vihod = idkcvih;
    }
    else
        return;
    
    int diametrp = Pipe::diametr_pipe();
    for (auto& [id, p]: pmap){
        if (p.diametr == diametrp && rebra.count(id) == 0 && p.remont == 0){
            rebra[id] = r;
            return;
        }
    }
    Pipe p;
    p.new_pipe();
    p.diametr = diametrp;
    p.remont = 0;
    pmap[p.getID()] = p;
    rebra[p.getID()] = r;
}

void PipeAndKC::delete_rebra(unordered_map <int, svyaz>& rebra){
    if (rebra.size() == 0){
        cout << "empty\n";
        return;
    }
    cout << "realno want delete?(y/n):";
    string s;
    INPUT_LINE(cin, s);
    if (s == "n"){
        return;
    }
    cout << "input id pipe for delete: ";
    int idp = get_correct(Pipe::MaxID, 1);
    if (rebra.count(idp)){
        rebra.erase(idp);
        return;
    }
    cout << "no such id\n";
}


unordered_set<int> PipeAndKC::number_vershin(const unordered_map<int, svyaz>& rebra){
    unordered_set<int> v;
    for (auto& [id, r] : rebra){
        v.insert(r.vhod);
        v.insert(r.vihod);
    }
    return v;
}
unordered_map<int, int> PipeAndKC::vershin_map(const unordered_map<int, svyaz>& rebra){
    unordered_map<int, int> vershin;
    unordered_set<int> v = number_vershin(rebra);
    int k = 1;
    for (int elem: v){
        vershin[k] = elem;
        k++;
    }
    return vershin;
}

int PipeAndKC::getKeyByValue(const unordered_map<int, int>& map, const int& value) {
    for (const auto& pair : map) {
        if (pair.second == value) {
            return pair.first; // Нашли значение, возвращаем ключ
        }
    }
    return int{};
}

vector<vector<int>> PipeAndKC::create_graph(const unordered_map <int, svyaz>& rebra){
    unordered_set<int> v = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);
    vector<vector<int>> graph(v.size());

    for (auto& [id, r] : rebra){
        graph[getKeyByValue(vershin, r.vhod) - 1].push_back(r.vihod);
    }
    return graph;
}

bool PipeAndKC::iscycle(vector<vector<int>>& graph, int w, vector<int>& visited, unordered_map<int, int>& vershin){
    visited[w] = 1;

    for(int to: graph[w]){
        if(visited[getKeyByValue(vershin, to)-1] == 0 && iscycle(graph, getKeyByValue(vershin, to)-1, visited, vershin)){
            return true;
        }
        else if(visited[getKeyByValue(vershin, to)-1] == 1){
            return true;
        }
    }
    visited[w] = 2;
    return false;
}

int PipeAndKC::getvalue(unordered_map<int, int>& vershin, int &k){
    for (auto& [id, idkc] : vershin){
        if(id == k){
            return idkc;
        }
    }
    return int{};
}

void PipeAndKC::topol_sort(vector<vector<int>>& graph, int w, vector<int>& visited, vector<int> &order, unordered_map<int, int>& vershin){
    visited[w-1] = 1;
    
    for(int to: graph[w-1]){
        if(!visited[getKeyByValue(vershin, to)-1]){
            topol_sort(graph, getKeyByValue(vershin, to), visited, order, vershin);
        }
    }
    
    order.push_back(vershin[w]);
    
}

void PipeAndKC::istopol(const unordered_map <int, svyaz>& rebra){
    unordered_set<int> v = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);
    vector<vector<int>> graph = create_graph(rebra);
    vector<int> visited(v.size());
    bool k = false;
    for(int w = 1; w <= v.size(); w++){
        if(!visited[w-1]){
            k = iscycle(graph, w, visited, vershin);
        }
    }
    if (k){
        cout << "cycle\n";
        return;
    }
    else{
        cout << "oki-doki\n";
        vector<int> order;
        vector<int> visitee(v.size());
        for (int w = 1; w <= v.size(); w++){
            if(!visitee[w-1]){
                topol_sort(graph, w, visitee, order, vershin);
            }
        }
        for (int w: order){
            cout << w << " ";
        }
        cout << endl;
    }
}
