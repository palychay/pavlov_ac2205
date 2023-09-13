#include <iostream>
#include <limits>
#include <string>

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


Pipe New_Pipe(){      //vvod new pipe
    Pipe p;
    cout << "New pipe\n";
    cout << "Input kilometr_name: ";
    cin >> p.kilometr_name;
    cout << "lengnth(km): ";
    cin >> p.length;
    cout << "Input diametr(mm): ";
    cin >> p.diametr;
    cout << "Input remont(0 or 1): ";
    cin >> p.remont;
    cout << endl;
    return p;
}

void Print_Pipe(Pipe p){   //output new pipe
    cout << p.kilometr_name << endl;
    cout << p.length << endl;
    cout << p.diametr << endl;
    cout << p.remont << endl;
    cout << endl;
}


KC New_KC(){        //vvod new kc
    KC kc;
    cout << "New kc\n";
    cout << "Input name: ";
    cin >> kc.name;
    cout << "kolich cehov: ";
    cin >> kc.kolich_ceh;
    cout << "working ceh: ";
    cin >> kc.kolich_ceh_v_rabote;
    cout << "Input effectivnost(from 0 to 1): ";
    cin >> kc.effectivnost;
    cout << endl;
    return kc;
}

void Print_KC(KC kc){   //output new kc
    cout << kc.name << endl;
    cout << kc.kolich_ceh << endl;
    cout << kc.kolich_ceh_v_rabote << endl;
    cout << kc.effectivnost << endl;
    cout << endl;
}




void Menu(){
    bool k = 1;
    while (k){
        cout << "Menu\n";
        cout << " 1. Добавить трубу\n";
        cout << " 2. Добавить КС\n";
        cout << " 3. Просмотр всех объектов\n";
        cout << " 4. Редактировать трубу\n";
        cout << " 5. Редактировать КС\n";
        cout << " 6. Сохранить\n";
        cout << " 7. Загрузить\n";
        cout << " 0. Выход\n";

        int choice;
        cout << "input number: ";
        cin >> choice;

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear(); // Очистить флаг ошибки ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистить буфер ввода
            continue;
            }
        
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 0:
        cout << "Goodbye!";
            k = 0;
            break;
        default:
            cout << "Вы ввели некорректное значение, пожалуйста, выберите цифру от 0 до 7\n";
            break;
        }
        
    }
}




int main(){
   /* Pipe p = New_Pipe();
    Print_Pipe(p);

    KC kc = New_KC();
    Print_KC(kc);*/
    Menu();
    return 0;
}