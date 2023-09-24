#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
        cin.ignore(1000, '\n');
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
}

void savepipe(Pipe p){
    ofstream save;
    save.open("pipes.txt");
    if (save.is_open() && p.length != 0 && p.diametr != 0) //rewrite
    {
        save << p.kilometr_name << endl;
        save << p.length << endl;
        save << p.diametr << endl;
        save << p.remont << endl;
    }
    save.close(); 
    cout << "File has been written" << endl;
}

Pipe loading_pipe(Pipe &p){
    ifstream in("pipes.txt");
    if (in.is_open() && !(in.peek() == EOF))
    {   
        in >> p.kilometr_name >> p.length >> p.diametr >> p.remont;
    }
    else{
        cout << "pipe.txt is empty\n";
        cout << endl;
    }
    in.close();
    return p;
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
        cin.ignore(1000, '\n');
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
}

void savekc(KC kc){
    ofstream savee;
    savee.open("kompressors_stat.txt");
    if (savee.is_open() && kc.kolich_ceh != 0) //rewrite
    {
        savee << kc.name << endl;
        savee << kc.kolich_ceh << endl;
        savee << kc.kolich_ceh_v_rabote << endl;
        savee << kc.effectivnost << endl;
    }
    savee.close();
}

KC loading_kc(KC &kc){
    
    ifstream in("kompressors_stat.txt");
    if (in.is_open() && !(in.peek() == EOF))
    {   
        in >> kc.name >> kc.kolich_ceh >> kc.kolich_ceh_v_rabote >> kc.effectivnost;
    }
    else{
        cout << "kompressors_stat.txt is empty\n";
        cout << endl;
    }
    in.close();
    return kc;
}


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
            savepipe(p);
            savekc(kc);
            }
            continue;
        }

        else if (choice == 7){
            ifstream in("pipes.txt");
            ifstream inn("kompressors_stat.txt");
            if ((in.is_open() && !(in.peek() == EOF)) && (inn.is_open() && !(inn.peek() == EOF))){
                loading_pipe(p);
                k1++;
                loading_kc(kc);
                k2++;
            }
            else{
                cout << "empty\n";
                cout << endl;
            }
            in.close();
            inn.close();
            
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