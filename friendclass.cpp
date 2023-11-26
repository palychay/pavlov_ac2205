#include "friendclass.h"
#include "correct_input.h"


ostream& operator << (ostream &out, const PipeAndKC::svyaz &r){
    out << "id vh: " << r.vhod << " " << "id vihod: " << r.vihod << " ";
    return out;
}

void PipeAndKC::see_rebra(const unordered_map <int, svyaz>& rebra){
    for (auto& [id, r] : rebra){
        cout << r << "id pipe: " << id << endl;
    }
}

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

int PipeAndKC::getKeyByValue(const std::unordered_map<int, int>& map, const int& value) {
    for (const auto& pair : map) {
        if (pair.second == value) {
            return pair.first; // Нашли значение, возвращаем ключ
        }
    }
    return int{};
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

vector<vector<int>> PipeAndKC::graph(const unordered_map<int, svyaz>& rebra){
    unordered_set<int> v = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);

    vector<vector<int>> graph(v.size(), vector<int>(v.size(), 0));
    for (auto& [id, r] : rebra){
        graph[getKeyByValue(vershin, r.vhod) - 1][getKeyByValue(vershin, r.vihod) - 1] = 1;
    }
    return graph;
}

bool PipeAndKC::cycle(vector<vector<int>> &graph, int v, vector<int> &visited){
    visited[v] = 1;

    for (int to : graph[v]){
        if (visited[to] == 0 && cycle(graph, to, visited) || visited[to] == 1){
            return true;
        }
    }
    visited[v] = 2;
    return false;
}

void PipeAndKC::topological_sort(const unordered_map<int, svyaz>& rebra){
    vector<vector<int>> g = graph(rebra);
    unordered_set<int> v = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);
    vector<int> visited(v.size());
    bool k = false;
    for (int vv = 0; vv < v.size(); vv++){
        if(!visited[vv]){
            k = cycle(g, vv, visited);
        }
    }
    if(k){
        cout << "graph has not cycle\n";
    }
    else{
        cout << "graph has cycle\n";
    }
}