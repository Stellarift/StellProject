#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX = 50;

struct Task {
    string name;
    int priority = 0;
    string desc;
    string date;
    string time;
};

Task tasks[MAX];
int taskCount = 0;

void save() {
    ofstream f("tasks.txt");
    f << taskCount << endl;
    for (int i = 0; i < taskCount; i++) {
        f << tasks[i].name << endl;
        f << tasks[i].priority << endl;
        f << tasks[i].desc << endl;
        f << tasks[i].date << endl;
        f << tasks[i].time << endl;
    }
    cout << "Сохранено!\n";
}

void load() {
    ifstream f("tasks.txt");
    if (f) {
        f >> taskCount;
        string temp;
        getline(f, temp);
        for (int i = 0; i < taskCount; i++) {
            getline(f, tasks[i].name);
            f >> tasks[i].priority;
            getline(f, temp);
            getline(f, tasks[i].desc);
            getline(f, tasks[i].date);
            getline(f, tasks[i].time);
        }
        cout << "Загружено: " << taskCount << endl;
    }
}

void show(int i) {
    cout << i + 1 << ". " << tasks[i].name;
    cout << " [";
    switch (tasks[i].priority) {
        case 1: cout << "Высокий"; break;
        case 2: cout << "Средний"; break;
        case 3: cout << "Низкий"; break;
        default: cout << "Не указан"; break;
    }
    cout << "]\n   " << tasks[i].desc;
    cout << "\n   " << tasks[i].date << " " << tasks[i].time << endl;
}

void showAll() {
    if (taskCount == 0) { 
        cout << "Список пуст!\n"; 
        return; 
    }
    for (int i = 0; i < taskCount; i++) {
        show(i);
    }
}

void add() {
    if (taskCount >= MAX) { 
        cout << "Достигнут лимит задач!\n"; 
        return; 
    }
    
    cout << "Название: "; 
    cin.ignore(); 
    getline(cin, tasks[taskCount].name);
    
    cout << "Приоритет (1-высокий, 2-средний, 3-низкий): "; 
    cin >> tasks[taskCount].priority;
    
    cout << "Описание: "; 
    cin.ignore(); 
    getline(cin, tasks[taskCount].desc);
    
    cout << "Дата (ДД.ММ.ГГГГ): "; 
    getline(cin, tasks[taskCount].date);
    
    cout << "Время (ЧЧ:ММ): "; 
    getline(cin, tasks[taskCount].time);
    
    taskCount++; 
    save(); 
    cout << "Задача добавлена!\n";
}

void del() {
    showAll(); 
    if (taskCount == 0) return;
    
    cout << "Номер для удаления: "; 
    int n; 
    cin >> n;
    
    if (n < 1 || n > taskCount) { 
        cout << "Неверный номер!\n"; 
        return; 
    }
    
    for (int i = n - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--; 
    save(); 
    cout << "Задача удалена!\n";
}

void edit() {
    showAll(); 
    if (taskCount == 0) return;
    
    cout << "Номер для редактирования: "; 
    int n; 
    cin >> n; 
    
    if (n < 1 || n > taskCount) { 
        cout << "Неверный номер!\n"; 
        return; 
    }
    
    int index = n - 1;
    
    cout << "Новое название: "; 
    cin.ignore(); 
    getline(cin, tasks[index].name);
    
    cout << "Новый приоритет (1-3): "; 
    cin >> tasks[index].priority;
    
    cout << "Новое описание: "; 
    cin.ignore(); 
    getline(cin, tasks[index].desc);
    
    cout << "Новая дата: "; 
    getline(cin, tasks[index].date);
    
    cout << "Новое время: "; 
    getline(cin, tasks[index].time);
    
    save(); 
    cout << "Задача изменена!\n";
}

void search() {
    if (taskCount == 0) { 
        cout << "Нет задач для поиска!\n"; 
        return; 
    }
    
    cout << "Поиск по: 1-названию, 2-приоритету, 3-описанию, 4-дате: ";
    int choice; 
    cin >> choice; 
    cin.ignore();
    
    bool found = false;
    
    switch (choice) {
        case 1: {
            cout << "Введите название: "; 
            string s; 
            getline(cin, s);
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].name.find(s) != string::npos) { 
                    show(i); 
                    found = true; 
                }
            }
            break;
        }
        case 2: {
            cout << "Введите приоритет (1-3): "; 
            int p; 
            cin >> p;
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].priority == p) { 
                    show(i); 
                    found = true; 
                }
            }
            break;
        }
        case 3: {
            cout << "Введите текст: "; 
            string s; 
            getline(cin, s);
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].desc.find(s) != string::npos) { 
                    show(i); 
                    found = true; 
                }
            }
            break;
        }
        case 4: {
            cout << "Введите дата: "; 
            string s; 
            getline(cin, s);
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].date == s) { 
                    show(i); 
                    found = true; 
                }
            }
            break;
        }
        default:
            cout << "Неверный выбор!\n";
            return;
    }
    
    if (!found) cout << "Задачи не найдены!\n";
}

void period() {
    if (taskCount == 0) { 
        cout << "Нет задач!\n"; 
        return; 
    }
    
    cout << "Задачи на: 1-сегодня, 2-завтра, 3-неделю: "; 
    int p; 
    cin >> p; 
    cin.ignore();
    
    cout << "Введите дату (ДД.ММ.ГГГГ): "; 
    string date; 
    getline(cin, date);
    
    bool found = false;
    cout << "\n--- Результаты ---\n";
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].date == date) { 
            show(i); 
            found = true; 
        }
    }
    
    if (!found) cout << "Задачи на выбранный период не найдены!\n";
}

void sortTasks() {
    if (taskCount == 0) { 
        cout << "Нет задач для сортировки!\n"; 
        return; 
    }
    
    cout << "Сортировка по: 1-приоритету, 2-дате: "; 
    int type; 
    cin >> type;
    
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            bool needSwap = false;
            
            switch (type) {
                case 1:
                    if (tasks[j].priority > tasks[j+1].priority) {
                        needSwap = true;
                    }
                    break;
                case 2:
                    if (tasks[j].date > tasks[j+1].date) {
                        needSwap = true;
                    }
                    break;
                default:
                    cout << "Неверный выбор!\n";
                    return;
            }
            
            if (needSwap) {
                Task temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
    
    cout << "Задачи отсортированы!\n"; 
    showAll();
}

void menu() {
    int choice;
    
    do {
        cout << "\n--------- СПИСОК ДЕЛ --------\n";
        cout << "1. Показать все задачи\n";
        cout << "2. Добавить задачу\n";
        cout << "3. Удалить задачу\n";
        cout << "4. Редактировать задачу\n";
        cout << "5. Поиск задач\n";
        cout << "6. Задачи на период\n";
        cout << "7. Сортировать задачи\n";
        cout << "8. Выход\n";
        cout << "--------------------------------\n";
        cout << "Выберите действие: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: showAll(); break;
            case 2: add(); break;
            case 3: del(); break;
            case 4: edit(); break;
            case 5: search(); break;
            case 6: period(); break;
            case 7: sortTasks(); break;
            case 8: cout << "Выход...\n"; break;
            default: cout << "Неверный выбор!\n"; break;
        }
        
    } while (choice != 8);
}

int main() {
    cout << "СПИСОК ДЕЛ\n";
    cout << "---------------------------\n";
    
    load();
    menu();
    save();
    
    return 0;
}