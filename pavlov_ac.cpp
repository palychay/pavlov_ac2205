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
    //cin.ignore(1000, '\n');
    cin >> ws;
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

void editpipe(Pipe &p){
    cout << "Признак в ремонте(0 - нет or 1 - да): ";
    p.remont = get_correct(true, false);
    cout << endl;
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
    cout << "Новая КС\n";
    cout << "Название: ";
    //cin.ignore(1000, '\n');
    cin >> ws;
    getline(cin, kc.name);
    cout << "Количество цехов: ";
    kc.kolich_ceh = get_correct(1500, 0);
    cout << "Количество работающих цехов.(Может возникнуть ошибка, если их будет больше всего кол-ва цехов.): ";
    kc.kolich_ceh_v_rabote = get_correct(kc.kolich_ceh, 0);
    cout << "Ввод эффективности(от 0 до 1, включая все числа между ними): ";
    kc.effectivnost = get_correct(1., 0.);
    cout << endl;
    return kc;
}

void Print_KC(KC kc){   //output new kc
    cout << "Ваша KC\n";
    cout << "Название КС: ";
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
    cout << "Количество работающих цехов.(Может возникнуть ошибка, если их будет больше всего кол-ва цехов.): ";
    kc.kolich_ceh_v_rabote = get_correct(kc.kolich_ceh, 0);
    cout << endl;
}


void save_data01(const Pipe &p, const KC &kc){
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
    cout << endl;
}

void save_data(const Pipe &p){
    ofstream savee;
    savee.open("data.txt");
    if (savee.is_open()) //rewrite
    {   
        savee << p.kilometr_name << endl;
        savee << p.length << endl;
        savee << p.diametr << endl;
        savee << p.remont << endl;
    }
    savee.close();
    cout << endl;
}

void save_data1(const KC &kc){
    ofstream savee;
    savee.open("data.txt");
    if (savee.is_open()) //rewrite
    {   
        savee << kc.name << endl;
        savee << kc.kolich_ceh << endl;
        savee << kc.kolich_ceh_v_rabote << endl;
        savee << kc.effectivnost << endl;
    }
    savee.close();
    cout << endl;
}


void load_pipe(Pipe &p){
    
}

int Menu(){
    Pipe p;
    p.diametr = -1;
    KC kc;
    kc.kolich_ceh = -1;
    while (true){
        cout << "Меню\n";
        cout << " 1. Добавить трубу\n";
        cout << " 2. Добавить КС\n";
        cout << " 3. Просмотр доступных объектов\n";
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
            kc = New_KC();
            break;

        case 3:
            if (p.diametr != -1 && kc.kolich_ceh == -1){
                Print_Pipe(p);
                cout << "КС - НЕТ!\n" << endl;
            }
            else if (p.diametr == -1 && kc.kolich_ceh != -1){
                Print_KC(kc);
                cout << "Трубы - НЕТ!\n" << endl;
            }
            else if (p.diametr == -1 && kc.kolich_ceh == -1){
                cout << "Объектов нет!\n" << endl;
            }
            else{
                Print_KC(kc);
                Print_Pipe(p);
            }
            break;

        case 4:
            if (p.diametr != -1){
                editpipe(p);
            }
            else{
                cout << "Такого объекта нет\n" << endl;
            }
            break;

        case 5:
            if (kc.kolich_ceh != -1){
                editkc(kc);
            }
            else{
                cout << "Такого объекта нет\n" << endl;
            }
            break;

        case 6:
            if (p.diametr != -1 && kc.kolich_ceh == -1){
                save_data(p);
                cout << "КС - НЕТ!\n" << endl;
            }
            else if (p.diametr == -1 && kc.kolich_ceh != -1){
                save_data1(kc);
                cout << "Трубы - НЕТ!\n" << endl;
            }
            else if (p.diametr == -1 && kc.kolich_ceh == -1){
                cout << "Объектов нет!\n" << endl;
            }
            else{
                save_data01(p, kc);
            }
            break;

        case 7:
            
            break;

        case 8:
            return 0;
            break;
        default:
            break;
        }
    }
}



int main(){
    Menu();
    return 0;
}