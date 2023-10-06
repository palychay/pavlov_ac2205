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

void Print_KC(const KC &kc){   //output new kc
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


bool is_empty_pipe(const Pipe &p){
    if (p.diametr == -1){
        return true;
    }
    else{
        return false;
    }
}

bool is_empty_kc(const KC &kc){
    if (kc.kolich_ceh == -1){
        return true;
    }
    else{
        return false;
    }
}

bool is_empty_file(){
    ifstream file("data.txt");
    return (file.peek() == ifstream::traits_type::eof());
}


ofstream& operator << (ofstream &fout, const Pipe &p){
    fout << "here_pipe\n" << p.kilometr_name << endl << p.length << endl << p.diametr << endl << p.remont << endl;
    return fout;

}

ofstream& operator << (ofstream &fout, const KC &kc){
    fout << "here_kc\n" << kc.name << endl << kc.kolich_ceh << endl << kc.kolich_ceh_v_rabote << endl << kc.effectivnost << endl;
    return fout;
}
        
void save_data(const Pipe &p, const KC &kc){
    if (is_empty_file()){
        ofstream fout("data.txt");
        if (is_empty_pipe(p) == true && is_empty_kc(kc) == true){
            cout << "Нет данных для сохранения\n";
        }
        else if (is_empty_pipe(p) == false && is_empty_kc(kc) == true){
            fout << p;
        }
        else if (is_empty_pipe(p) == true && is_empty_kc(kc) == false){
            fout << kc;
        }
        else{
            fout << p << kc;
        }
        fout.close();
    }
    else{
        if (is_empty_pipe(p) == true && is_empty_kc(kc) == true){
            cout << "Нет данных для сохранения\n";
        }
        else{
            cout << "Файл не пуст. Вы точно хотите перезаписать данные?(yes/no): ";
            string s;
            cin >> s;
            if (s == "yes"){
                ofstream fout("data.txt");
                if (is_empty_pipe(p) == false && is_empty_kc(kc) == true){
                    fout << p;
                    }
                else if (is_empty_pipe(p) == true && is_empty_kc(kc) == false){
                    fout << kc;
                    }
                else if (is_empty_pipe(p) == false && is_empty_kc(kc) == false){
                    fout << p << kc;
                    }
                fout.close();
            }
            else{
                cout << "Выберите другой файл для сохранения\n";
            }
        }
    }
}


void write_in_massiv(vector <string> &datf){
    ifstream finn("data.txt");
    string s;
    while (getline(finn, s))
    {
        datf.push_back(s);
    }
    finn.close();
}

void load_data(Pipe &p, KC &kc){
    if (is_empty_file()){
        cout << "Нет данных для загрузки\n";
    }
    else{
        ifstream fin("data.txt");
        vector <string> datf;
        write_in_massiv(datf);
        string s1, s2, s3, s4;
        if (fin.is_open()){

        if (datf[0] == "here_pipe" && datf[5] != "here_kc"){
            p.kilometr_name = datf[1];
            fin >> s1 >> s2 >> p.length >> p.diametr >> p.remont;
        }

        else if(datf[0] == "here_kc"){
            kc.name = datf[1];
            fin >> s1 >> s2 >> kc.kolich_ceh >> kc.kolich_ceh_v_rabote >> kc.effectivnost;
        }
        else if(datf[0] == "here_pipe" && datf[5] == "here_kc"){
            fin >> s1 >> s2 >> p.length >> p.diametr >> p.remont >>
             s3 >> s4 >> kc.kolich_ceh >> kc.kolich_ceh_v_rabote >> kc.effectivnost;
        }
        }
        fin.close();
    }
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
            if (is_empty_pipe(p) == false && is_empty_kc(kc) == true){
                Print_Pipe(p);
                cout << "КС - НЕТ!\n" << endl;
            }
            else if (is_empty_pipe(p) == true && is_empty_kc(kc) == false){
                Print_KC(kc);
                cout << "Трубы - НЕТ!\n" << endl;
            }
            else if (is_empty_pipe(p) == true && is_empty_kc(kc) == true){
                cout << "Объектов нет!\n" << endl;
            }
            else{
                Print_Pipe(p);
                Print_KC(kc);
            }
            break;

        case 4:
            if (!(is_empty_pipe(p))){
                editpipe(p);
            }
            else{
                cout << "Такого объекта нет\n" << endl;
            }
            break;

        case 5:
            if (!(is_empty_kc(kc))){
                editkc(kc);
            }
            else{
                cout << "Такого объекта нет\n" << endl;
            }
            break;

        case 6:
            save_data(p, kc);
            break;

        case 7:
            load_data(p, kc);
            break;

        case 8:
            return 0;

        default:
            break;
        }
    }
}


int main(){
    Menu();
    return 0;
}