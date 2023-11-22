#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "pipe.h"
#include "kc.h"

class PipeAndKC
{
    public:
    struct svyaz
    {
        KC vhod;
        KC vihod;
        Pipe line;
    };

    void create_rebro(const unordered_map <int, KC>& kcmap, unordered_map <int, Pipe>& pmap, unordered_map <int, svyaz>& rebra);

    void load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap);
    void save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap);
    bool is_empty_file(const string &s);

};