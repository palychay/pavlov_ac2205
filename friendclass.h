#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "pipe.h"
#include "kc.h"

class PipeAndKC
{
    public:
    void load_data(unordered_map<int, Pipe> &pmap, unordered_map<int, KC> &kcmap);
    void save_data(const unordered_map<int, Pipe> &pmap, const unordered_map<int, KC> &kcmap);
    bool is_empty_file(const string &s);
};