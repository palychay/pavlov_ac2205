#include <iostream>

using namespace std;

struct Pipe  // труба
{
    string kilometr_name;
    double length;
    int diametr;
    bool remont;
};

struct KC // компрессорная станция
{
    string name;
    int kolich_ceh;
    int kolich_ceh_v_rabote;
    double effectivnost;
};

Pipe New_Pipe(){
    Pipe p;
    cin >> p.kilometr_name >> p.length >> p.diametr >> p.remont;
    return p;
}

void Print_Pipe(Pipe p){
    cout << p.kilometr_name << endl;
    cout << p.length << endl;
    cout << p.diametr << endl;
    cout << p.remont << endl;
}

int main(){
    Pipe p = New_Pipe();
    Print_Pipe(p);
    return 0;
}