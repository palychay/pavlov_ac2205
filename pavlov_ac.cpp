#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool isDouble(const string &input) {
    istringstream iss(input);
    double testValue;
    iss >> noskipws >> testValue;
    return iss.eof() && !iss.fail() && testValue > 0;
}

bool isInteger(const string &input) {
    istringstream iss(input);
    int testValue;
    iss >> testValue;
    return iss.eof() && !iss.fail() && testValue > 0;
}

bool isBool(const string &input) {
    istringstream iss(input);
    bool testValue;
    iss >> testValue;
    return iss.eof() && !iss.fail();
}

struct Pipe  // труба
{
    string kilometr_name;
    double length;
    int diametr;
    bool remont;
};

Pipe New_Pipe(Pipe &p){      //vvod new pipe
    
    cout << "New pipe\n";
    cout << "Input kilometr_name: ";
    cin.ignore(1000, '\n');
    getline(cin, p.kilometr_name);

    while (true){
    string input;
    cout << "lengnth(km): ";
    getline(cin, input);
    if (isDouble(input)){
         istringstream iss(input);
         iss >> noskipws >> p.length;
         break;
    }
    else{
        cout << "uncorrect input. programm need double\n";
        continue;
    }
    }

    while (true)
    {
        cout << "Input diametr(mm): ";
        string input;
        getline(cin, input);
        if (isInteger(input)){
            istringstream iss(input);
            iss >> p.diametr;
            break;
        }
        else{
            cout << "uncorrect input. need int number\n";
            continue;
        }
    }

    while (true)
    {   string input;
        cout << "Input remont(0 - no or 1 - yes): ";
        getline(cin, input);
        if (isBool(input)){
            istringstream iss(input);
            iss >> p.remont;
            break;
        }
    else{
        cout << "uncorrect input. need 0 or 1\n";
        continue;
    }
    }

    cout << endl;
    return p;
}

void Print_Pipe(Pipe p){   //output new pipe
    cout << "Your pipe:\n";
    cout << "Kilometr name: ";
    cout << p.kilometr_name << endl;
    cout << "Length(kilometrs): ";
    cout << p.length << endl;
    cout << "Diametr(mm): ";
    cout << p.diametr << endl;
    cout << "Remont(0 - no, 1 - yes): ";
    cout << p.remont << endl;
    cout << endl;
}

void editpipe(Pipe &p){
    while (true)
        {
        string input;
        cout << "Input remont(0 - no or 1 - yes): ";
        cin >> input;
        if (isBool(input)){
            istringstream iss(input);
            iss >> p.remont;
            break;
        }
    else{
        cout << "uncorrect input. need 0 or 1\n";
        continue;
    }
            
        }
}



struct KC // компрессорная станция
{
    string name;
    int kolich_ceh;
    int kolich_ceh_v_rabote;
    double effectivnost;
};

KC New_KC(){        //vvod new kc
    KC kc;
    cout << "New kc\n";
    cout << "Input name: ";
    cin.ignore(1000, '\n');
    getline(cin, kc.name);

    while (true){
    string input;
    cout << "kolich cehov: ";
    getline(cin, input);
    if (isInteger(input)){
        istringstream iss(input);
        iss >> kc.kolich_ceh;
        break;
    }
    else{
        cout << "uncorrect input. need int number\n";
        continue;
    }
    }

    while (true)
    {   string input;
        cout << "working ceh: ";
        getline(cin, input);
        if (isInteger(input)){
            istringstream iss(input);
            iss >> kc.kolich_ceh_v_rabote;
            if (kc.kolich_ceh < kc.kolich_ceh_v_rabote){
                cout << "uncorrect input. need int number or kolich_ceh < kolich_ceh_v_rabote\n";
                continue;
            }
            else{
                break;
            }
        }
        else{
            cout << "uncorrect input. need int number or kolich_ceh < kolich_ceh_v_rabote\n";
            continue;
        }
    }
    
    while (true)
    {   string input;
        cout << "Input effectivnost(from 0 to 1): ";
        getline(cin, input);
        if (isDouble(input)){
            istringstream iss(input);
            iss >> kc.effectivnost;
            if (kc.effectivnost > 1){
                cout << "uncorrect input. need double number\n";
                continue;
            }
            else{
                break;
            }
        }
        else{
            cout << "uncorrect input. need double number\n";
            continue;
        }
    }
    
    cout << endl;
    return kc;
}

void Print_KC(KC kc){   //output new kc
    cout << "Your KC\n";
    cout << "KC name: ";
    cout << kc.name << endl;
    cout << "Количество цехов: ";
    cout << kc.kolich_ceh << endl;
    cout << "Количество цехов в работе ";
    cout << kc.kolich_ceh_v_rabote << endl;
    cout << "Эффективность КС: ";
    cout << kc.effectivnost << endl;
    cout << endl;
}

void editkc(KC &kc){
    while (true)
    {
        string input;
        cout << "working ceh: ";
        cin >> input;
        if (isInteger(input)){
            istringstream iss(input);
            iss >> kc.kolich_ceh_v_rabote;
            if (kc.kolich_ceh < kc.kolich_ceh_v_rabote){
                cout << "uncorrect input. need int number or kolich_ceh < kolich_ceh_v_rabote\n";
                continue;
            }
            else{
                break;
            }
        }
        else{
            cout << "uncorrect input. need int number or kolich_ceh < kolich_ceh_v_rabote\n";
            continue;
        }
    }
}



void save_data(Pipe p, KC kc){
    ofstream savee;
    savee.open("data.txt");
    if (savee.is_open()) //rewrite
    {   
        savee << p.kilometr_name << endl;
        savee << p.length << endl;
        savee << p.diametr << endl;
        savee << p.remont << endl;
        savee << kc.name << endl;
        savee << kc.kolich_ceh << endl;
        savee << kc.kolich_ceh_v_rabote << endl;
        savee << kc.effectivnost << endl;
    }
    savee.close();
    cout << "ok save" << endl;
}


vector <string> write_load_data_in_massiv(){
    vector <string> star;
    string s;
    ifstream in("data.txt");
    if (in.is_open() && !(in.eof())){
        int i = 0;
        while (i < 8)
        {   getline(in, s);
            star.push_back(s);
            i++;
        }
    }
    return star;
}

void loading_pipe(Pipe &p, KC &kc){
    vector <string> ps = write_load_data_in_massiv();
    p.kilometr_name = ps[0];
    istringstream pl(ps[1]);
    istringstream pd(ps[2]);
    istringstream pr(ps[3]);
    pl >> p.length;
    pd >> p.diametr;
    pr >> p.remont;
    kc.name = ps[4];
    istringstream kcceh(ps[5]);
    istringstream kcw(ps[6]);
    istringstream kcef(ps[7]);
    kcceh >> kc.kolich_ceh;
    kcw >> kc.kolich_ceh_v_rabote;
    kcef >> kc.effectivnost;
    cout << "loading finished" << endl;
}
/*KC loading_kc(KC kc){
    vector <string> kcs = write_load_data_in_massiv();
    kc.name = kcs[4];
    istringstream kcceh(kcs[5]);
    istringstream kcw(kcs[6]);
    istringstream kcef(kcs[7]);
    kcceh >> kc.kolich_ceh;
    kcw >> kc.kolich_ceh_v_rabote;
    kcef >> kc.effectivnost;
    return kc;
}*/


void Menu(){
    Pipe p;
    KC kc;
    int k1 = 0;
    int k2 = 0;
    while (true){
        cout << "Menu\n";
        cout << " 1. Добавить трубу\n";
        cout << " 2. Добавить КС\n";
        cout << " 3. Просмотр всех объектов\n";
        cout << " 4. Редактировать трубу\n";
        cout << " 5. Редактировать КС\n";
        cout << " 6. Сохранить\n";
        cout << " 7. Загрузить\n";
        cout << " 8. Выход\n";
        cout << endl;
        double choice;
        cout << "input number: ";
        cin >> choice;
        cout << endl;

        if (choice == 1){
            New_Pipe(p);
            k1++;
            continue;
        }

        else if (choice == 2){
            kc = New_KC();
            k2++;
            continue;
        }

        else if (choice == 3){
            if (k1 == 0 || k2 == 0){
                cout << "Empty or not pipe or kc(\n";
            }
            else{
                Print_Pipe(p);
                Print_KC(kc);
            }
            continue;
        }

        else if (choice == 4){
            if (k1 == 0){
                cout << "Empty\n";
                cout << endl;
            }
            else{
            editpipe(p);}
            continue;
        }

        else if (choice == 5){
            if (k2 == 0){
                cout << "Empty\n";
                cout << endl;
            }
            else{
            editkc(kc);}
            continue;
        }

        else if (choice == 6){
            if (k1 == 0 || k2 == 0){
                cout << "Empty\n";
                cout << endl;
            }
            else{
            save_data(p, kc);
            }
            continue;
        }

        else if (choice == 7){
            ifstream in("data.txt");
            if (in.is_open() && !(in.peek() == EOF)){
                loading_pipe(p, kc);
                k1++;
                //loading_kc(kc);
                k2++;
            }
            else{
                cout << "empty\n";
                cout << endl;
            }
            in.close();  
        }

        else if (choice == 8){
            cout << "Goodbye!";
            break;
        }

        else{
            cout << "Вы ввели некорректное значение, пожалуйста, выберите цифру от 1 до 8\n";
            cin.clear(); // Очистить флаг ошибки ввода
            cin.ignore(1000, '\n'); 
        }
    }
}



int main(){
    Menu();
    return 0;
}