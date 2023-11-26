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

    int getKeyByValue(const std::unordered_map<int, int>& map, const int& value);

    void create_rebro(const unordered_map <int, KC>& kcmap, unordered_map <int, Pipe>& pmap, unordered_map <int, svyaz>& rebra);
    void see_rebra(const unordered_map <int, svyaz>& rebra);
    vector<vector<int>> graph(const unordered_map<int, svyaz>& rebra);
    bool cycle(vector<vector<int>> &graph, int v, vector<int> &visited);
    void topological_sort(const unordered_map<int, svyaz>& rebra);

    unordered_set<int> number_vershin(const unordered_map<int, svyaz>& rebra);
    unordered_map<int, int> vershin_map(const unordered_map<int, svyaz>& rebra);

    void load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap);
    void save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap);
    bool is_empty_file(const string &s);

    friend std::ostream& operator << (std::ostream& out, const svyaz &r);
};