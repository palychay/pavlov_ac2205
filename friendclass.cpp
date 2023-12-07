#include "friendclass.h"
#include "correct_input.h"


ostream& operator << (ostream &out, const PipeAndKC::svyaz &r){
    out << "id vh: " << r.vhod << " " << "id vihod: " << r.vihod << " ";
    return out;
}

ofstream& operator << (ofstream &fout, const unordered_map<int, PipeAndKC::svyaz> &rebra){
    
    for (auto& [id, r] : rebra){
        fout << "here_rebra\n";
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
    rebra.clear();
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


int PipeAndKC::ves_vershin(const int& pid, const unordered_map <int, Pipe>& pmap){
    for (auto [id, p]: pmap){
        if (pid == id)
            return p.length;
    }
    return 1e9;
}

bool PipeAndKC::value_in_vector(const vector<int>& visited, const int& t){
    for (int tr: visited){
        if (t == tr){
            return true;
        }
    }
    return false;
}

void PipeAndKC::zapolnit_postoyan(vector<vector<int>> &dejk, const int& k, const int& ves, const int& l){
    for (int i = (l-1); i < dejk.size(); i++){
        dejk[i][k] = ves;
    }
}

int PipeAndKC::id_pipe_for_ves(const unordered_map<int, svyaz> &rebra, int& idpvh, int& idpvih){
    for(auto& [id, r]: rebra){
        if(idpvh == r.vhod && idpvih == r.vihod){
            return id;
        }
    }
    return 1e9;
}

void PipeAndKC::dejkstra(const unordered_map <int, svyaz>& rebra, const unordered_map <int, Pipe>& pmap){
    if (rebra.size() == 0){
        return;
    }
    else{
    unordered_set<int> v = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);
    vector<vector<int>> graph = create_graph(rebra);
    const int INF = 1e9;

    cout << "vvod start:";
    int start = get_correct(KC::MaxID, 1);
    cout << "vvod finish: ";
    int finish = get_correct(KC::MaxID, 1);

    if (start == finish){
        cout << start << "->" << finish << " = " << "0\n";
    }
    else{
        vector<int> visited(v.size(), INF); // вектор временных веток
        vector<vector<int>> dejk;

        dejk.assign(v.size() + 1, vector<int>(v.size(), INF)); // заполнение матрицы бесконечностями
        int vrp = 0; // вес постояннаянной метки
        int k = 1; // кол-во шагов выполнения
        int p = getKeyByValue(vershin, start) - 1; // какая вершина с постоянной меткой
        visited.push_back(p);
        dejk[0][getKeyByValue(vershin, start) - 1]= vrp;

        while (k <= v.size())
        {   
            int m = INF;
            int pk;
            zapolnit_postoyan(dejk, p, vrp, k);
            for(int i = 0; i < v.size(); i++){
                if (!(value_in_vector(visited, i))){
                    if(dejk[k-1][i] > vrp + ves_vershin(id_pipe_for_ves(rebra, vershin[p+1], vershin[i+1]), pmap)){
                        dejk[k][i] =  vrp + ves_vershin(id_pipe_for_ves(rebra, vershin[p+1], vershin[i+1]), pmap);
                    }
                    else{
                        dejk[k][i] = dejk[k-1][i];
                    }
                    if(m >= dejk[k][i] ){
                        m = dejk[k][i];
                        pk = i;
                    }
                }
            }
            vrp = m;
            p = pk;
            visited.push_back(p);
            k++;
        }
        if (dejk[v.size()][getKeyByValue(vershin, finish)-1] == 1e9){
            cout << "net putya\n";
            return;
        }
        cout << start << "->" << finish << " = " << dejk[v.size()][getKeyByValue(vershin, finish)-1] << endl;
        vector <int> s;
        put_from_dejk(dejk, start, finish, vershin, graph, rebra, pmap, s, v);
        vector<int> path (s.rbegin(), s.rend());
        for (int v: path){
            cout << v << " - ";
        }
        cout << "|" << endl;
    }
    }
}


void PipeAndKC::put_from_dejk(const vector<vector<int>>& dejk, const int& start, const int& finish, unordered_map<int, int>& vershin, const vector<vector<int>>& graph, const unordered_map <int, svyaz>& rebra, const unordered_map <int, Pipe>& pmap, vector<int>& s,  const unordered_set<int>& v){
    
    s.push_back(finish);
    int k = finish;
    for (int t: v){
        if (dejk[dejk.size() - 1][getKeyByValue(vershin, t) - 1] + ves_vershin(id_pipe_for_ves(rebra, t, k), pmap) == dejk[dejk.size() - 1][getKeyByValue(vershin, k) - 1] && !value_in_vector(s, start)){
            put_from_dejk(dejk, start, t, vershin, graph, rebra, pmap, s, v);
        }
    }
}


int PipeAndKC::proizv(const unordered_map <int, Pipe>& pmap, const int& idpipe){
    int proizvoditenlost = 0;
    for(auto [id, p]: pmap){
        if (idpipe == id && p.remont != true){
            proizvoditenlost = (pow(p.diametr/10, 3) / p.length*100);
            return proizvoditenlost;
        }
    }
    return proizvoditenlost;
}



vector <vector<int>>PipeAndKC::matriza_vesov(const unordered_map <int, svyaz>& rebra, const unordered_map <int, Pipe>& pmap){
    unordered_set<int> v = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);
    vector<vector<int>> graph = create_graph(rebra);

    vector <vector<int>> matriza_vesov;
    matriza_vesov.assign(v.size(), vector<int>(v.size(), 0));
     for (auto [id, r] : rebra){
        matriza_vesov[getKeyByValue(vershin, r.vhod) - 1][getKeyByValue(vershin, r.vihod) - 1] = proizv(pmap, id);
    }
    return matriza_vesov;
}


void PipeAndKC::max_potok(const unordered_map <int, svyaz>& rebra, const unordered_map <int, Pipe>& pmap){
    if(rebra.size() == 0){
        return;
    }
    unordered_set<int> vr = number_vershin(rebra);
    unordered_map<int, int> vershin = vershin_map(rebra);
    vector<vector<int>> graph = create_graph(rebra);
    cout << "vvod id istoka: ";
    int istok = get_correct(KC::MaxID, 1);
    cout << "vvod id stoka: ";
    int stok = get_correct(KC::MaxID, 1);
    if (istok == stok){
        cout << "max flow from " << istok << " to " << stok << "= 0\n";
        return;
    }

    int source = getKeyByValue(vershin, istok) - 1;
	int sink = getKeyByValue(vershin, stok) - 1;
    int num_V = vr.size();
	// Создаем резервную матрицу для хранения остаточных пропускных способностей
	vector<vector<int>> r_matrix = matriza_vesov(rebra, pmap);

	vector<int> parent(num_V, -1); // 
	int max_flow = 0;

	while (true) {
		// Заполняется с помощью обхода в ширину и хранит пути
		parent.assign(num_V, -1);
		queue<pair<int, int>> q;
		q.push({ source, 1e9 });
		parent[source] = source;

		while (!q.empty()) {
			int u = q.front().first;
			int path_flow = q.front().second;
			q.pop();

			for (int v = 0; v < num_V; v++) {
				if (parent[v] == -1 && r_matrix[u][v] > 0) {
					// Найден непосещенный узел с ненулевой пропускной способностью в резервной матрице
					parent[v] = u;
					int min_capacity = minimum(path_flow, r_matrix[u][v]);
					if (v == sink) {
						// Если достигнут сток, обновляем пропускные способности на пути
						while (v != source) {
							u = parent[v];
							r_matrix[u][v] -= min_capacity;
							r_matrix[v][u] += min_capacity;
							v = u;
						}
						max_flow += min_capacity;
						break;
					}
					q.push({ v, min_capacity });
				}
			}
		}
		// Если BFS не может найти путь, завершаем цикл
		if (parent[sink] == -1)
			break;
	}
	cout << "max flow from " << istok << " to " << stok << "= " << max_flow << endl;

}
