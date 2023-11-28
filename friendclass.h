#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include "pipe.h"
#include "kc.h"


class PipeAndKC
{
    public:
    struct svyaz
    {
        int vhod;
        int vihod;
    };

    vector<vector<int>> create_graph(const unordered_map <int, svyaz>& rebra);
    unordered_set<int> number_vershin(const unordered_map<int, svyaz>& rebra);
    unordered_map<int, int> vershin_map(const unordered_map<int, svyaz>& rebra);
    int getKeyByValue(const unordered_map<int, int>& map, const int& value);
    bool iscycle(vector<vector<int>>& graph, int w, vector<int>& visited,  unordered_map<int, int>& vershin);
    void istopol(const unordered_map <int, svyaz>& rebra);
    int getvalue(unordered_map<int, int>& vershin, int &k);
    void topol_sort(vector<vector<int>>& graph, int w, vector<int>& visited, vector<int> &order, unordered_map<int, int>& vershin);

    void create_rebro(const unordered_map <int, KC>& kcmap, unordered_map <int, Pipe>& pmap, unordered_map <int, svyaz>& rebra);
    void see_rebra(const unordered_map <int, svyaz>& rebra);
    void delete_rebra(unordered_map <int, svyaz>& rebra);

    void load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap, unordered_map <int, svyaz>& rebra);
    void save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap, const unordered_map <int, svyaz>& rebra);
    bool is_empty_file(const string &s);

    friend std::ostream& operator << (std::ostream& out, const svyaz &r);
    friend std::ofstream& operator << (ofstream &fout, const unordered_map<int, svyaz> &rebra);

};