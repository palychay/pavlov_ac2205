#include "kc.h"
#include "correct_input.h"

void KC::new_kc(){
    cout << "new kc\n";
    cout << "name: ";
    cin >> ws;
    getline(cin, name);
    cout << "number of workshops: ";
    kolich_ceh = get_correct(1500, 0);
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    kolich_ceh_v_rabote = get_correct(kolich_ceh, 0);
    cout << "Efficiency input(from 0 to 1, including all numbers between them): ";
    effectivnost = get_correct(1., 0.);
    cout << endl;
}

void KC::Print_KC() const{
    cout << "your kc\n";
    cout << "name kc: ";
    cout << name << endl;
    cout << "Number of workshops: ";
    cout << kolich_ceh << endl;
    cout << "Number of workshops in operation: ";
    cout << kolich_ceh_v_rabote << endl;
    cout << "kc efficiency: ";
    cout << effectivnost << endl;
    cout << endl;
}

void KC::editkc(){
    cout << "The number of working workshops.(An error may occur if there are more of them than the total number of workshops.): ";
    kolich_ceh_v_rabote = get_correct(kolich_ceh, 0);
    cout << endl;
}

bool KC::is_empty_kc() const{
    if (kolich_ceh == -1){
        return true;
    }
    else{
        return false;
    }
}