#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include "pipe.h"
#include "kc.h"
#include <stack>
#include <queue>

class PipeAndKC
{
    public:
    struct svyaz
    {
        int vhod;
        int vihod;
    };

    

    void create_rebro(const unordered_map <int, KC>& kcmap, unordered_map <int, Pipe>& pmap, unordered_map <int, svyaz>& rebra);
    void see_rebra(const unordered_map <int, svyaz>& rebra);
    void delete_rebra(unordered_map <int, svyaz>& rebra);

    void load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap, unordered_map <int, svyaz>& rebra);
    void save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap, const unordered_map <int, svyaz>& rebra);
    bool is_empty_file(const string &s);

    friend std::ostream& operator << (std::ostream& out, const svyaz &r);
    friend std::ofstream& operator << (ofstream &fout, const unordered_map<int, svyaz> &rebra);

};