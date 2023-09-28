#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template <typename T> 
T get_correct(T max, T min){
    T x;
	while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max)	// is buffer empty (int/float check)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Неправильный ввод. Пожалуйста, введите еще раз:  ";
	}
    return x;
}


struct Pipe  // труба
{
    string kilometr_name;
    double length;
    int diametr;
    bool remont;
};

Pipe New_Pipe(){      //vvod new pipe
    Pipe p;
    cout << "Новая труба\n";
    cout << "Километровая отметка: ";
    cin.ignore(1000, '\n');
    getline(cin, p.kilometr_name);
    cout << "Длина(км): ";
    p.length = get_correct(1500., 0.);
    cout << "Диаметр трубы(мм): ";
    p.diametr = get_correct(1500, 0);
    cout << "Признак в ремонте(0 - нет or 1 - да): ";
    p.remont = get_correct(true, false);
    cout << endl;
    return p;
}

void Print_Pipe(const Pipe &p){   //output new pipe
    cout << "Ваша труба:\n";
    cout << "Километровая отметка: ";
    cout << p.kilometr_name << endl;
    cout << "Длина(в километрах): ";
    cout << p.length << endl;
    cout << "Диаметр трубы(в миллиметрах): ";
    cout << p.diametr << endl;
    cout << "Признак в ремонте(0 - нет, 1 - да): ";
    cout << p.remont << endl;
    cout << endl;
}
/*
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
*/

/*
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

*/

int Menu(){
    Pipe p;
    //KC kc;
   // int k1 = 0;
    //int k2 = 0;
    while (true){
        cout << "Меню\n";
        cout << " 1. Добавить трубу\n";
        cout << " 2. Добавить КС\n";
        cout << " 3. Просмотр всех объектов\n";
        cout << " 4. Редактировать трубу\n";
        cout << " 5. Редактировать КС\n";
        cout << " 6. Сохранить\n";
        cout << " 7. Загрузить\n";
        cout << " 8. Выход\n";
        cout << endl;
        int choice;//!!!
        cout << "Пожалуйста, выберите число от 1 до 8: ";
        choice = get_correct(8, 1);
        cout << endl;
        switch (choice)
        {
        case 1:
            p = New_Pipe();
            break;
        case 2:
            
            break;
        case 3:
            Print_Pipe(p);
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        case 6:
            
            break;
        case 7:
            
            break;
        case 8:
            return 0;
            break;
        default:
            cout << "Ошибка ввода. Пожалуйста, выберите число от 1 до 8.";
            break;
        }
    }
}



int main(){
    Menu();
    return 0;
}