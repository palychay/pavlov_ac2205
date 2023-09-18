#include <iostream>
#include <fstream>

using namespace std;

struct Pipe  // труба
{
    string kilometr_name;
    double length;
    int diametr;
    bool remont;
};

Pipe New_Pipe(){      //vvod new pipe
    Pipe p;
    cout << "New pipe\n";
    cout << "Input kilometr_name: ";
    cin >> p.kilometr_name;

    while (true){
    cout << "lengnth(km): ";
    cin >> p.length;
    if (cin.fail() || p.length < 0){
        cout << "uncorrect input. need double number\n";
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }
    else{
        break;
    }
    }

    while (true)
    {
        cout << "Input diametr(mm): ";
        cin >> p.diametr;
        if (cin.fail() || p.diametr < 0){
            cout << "uncorrect input. need int number\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        else{
            break;
        }
    }

    while (true)
    {
        cout << "Input remont(0 - no or 1 - yes): ";
        cin >> p.remont;
        if (cin.fail()){
            cout << "uncorrect input. need 0 or 1\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
    else{
        break;
    }
    }

    cout << endl;
    return p;
}

void Print_Pipe(Pipe p){   //output new pipe
    cout << "Your pipe:\n";

    cout << "Kilometr name: ";
    cout << p.kilometr_name << endl;
    cout << "Length(metrs): ";
    cout << p.length << endl;
    cout << "Diametr: ";
    cout << p.diametr << endl;
    cout << "Remont(0 - no, 1 - yes): ";
    cout << p.remont << endl;
    cout << endl;
}

void editpipe(Pipe &p){
    while (true)
             {
            cout << "Edit remont pipe(0 - no or 1 - yes): ";
            cin >> p.remont;
            if (cin.fail()){
                cout << "uncorrect input. need 0 or 1\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
                }
            else{
                break;
            }
            continue;
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
    cin >> kc.name;

    while (true){
    cout << "kolich cehov: ";
    cin >> kc.kolich_ceh;
    if ((cin.fail()) || kc.kolich_ceh < 0){
        cout << "uncorrect input. need int number\n";
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }
    else{
        break;
    }
    }

    while (true)
    {
        cout << "working ceh: ";
        cin >> kc.kolich_ceh_v_rabote;
        if ((!cin) || kc.kolich_ceh_v_rabote <= 0 || kc.kolich_ceh < kc.kolich_ceh_v_rabote){
        cout << "uncorrect input. need int number or kolich_ceh < kolich_ceh_v_rabote\n";
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }
    else{
        break;
    }
    }
    
    while (true)
    {
        cout << "Input effectivnost(from 0 to 1): ";
        cin >> kc.effectivnost;
        if (cin.fail() || kc.effectivnost <= 0 || kc.effectivnost >= 1){
        cout << "uncorrect input. need double number\n";
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }
    else{
        break;
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
            p = New_Pipe();
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
            continue;
        }

        else if (choice == 6){
            continue;
        }

        else if (choice == 7){
            continue;
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