#include "fileio.h"
#include <iostream>
#include <fstream>
using namespace std;

Task tasks[MAX_TASKS];
int taskCount = 0;

void saveToFile() {
    ofstream f("tasks.txt");
    f << "Всего задач: " << taskCount << "\n\n";
    
    for (int i = 0; i < taskCount; i++) {
        f << "------------- ЗАДАЧА " << i + 1 << " ---------\n";
        f << "Название: " << tasks[i].name << "\n";
        f << "Статус: " << (tasks[i].completed ? "ВЫПОЛНЕНА" : "НЕ ВЫПОЛНЕНА") << "\n";
        f << "Приоритет: ";
        
        switch (tasks[i].priority) {
            case 1: f << "Высокий"; 
            break;
            case 2: f << "Средний"; 
            break;
            case 3: f << "Низкий"; 
            break;
            default: f << "Не указан"; 
            break;
        }
        f << "\n";
        
        f << "Описание: " << tasks[i].desc << "\n";
        f << "Дата: " << tasks[i].date << "\n";
        f << "Время: " << tasks[i].time << "\n";
        f << "---------------------------\n\n";
    }
    
    f.close();
    cout << "Задачи сохранены в файл tasks.txt!\n";
}

void loadFromFile() {
    ifstream f("tasks.txt");
    if (f) {
        string temp;
        getline(f, temp);
        getline(f, temp);
        
        taskCount = 0;
        
        while (getline(f, temp)) {
            if (temp.find("------------- ЗАДАЧА") != string::npos) {
                getline(f, temp);
                tasks[taskCount].name = temp.substr(10);
                
                getline(f, temp);
                string status = temp.substr(7);
                tasks[taskCount].completed = (status.find("ВЫПОЛНЕНА") != string::npos);
                
                getline(f, temp);
                string prio = temp.substr(11);
                if (prio == "Высокий") tasks[taskCount].priority = 1;
                else if (prio == "Средний") tasks[taskCount].priority = 2;
                else if (prio == "Низкий") tasks[taskCount].priority = 3;
                else tasks[taskCount].priority = 0;
                
                getline(f, temp);
                tasks[taskCount].desc = temp.substr(10);
                
                getline(f, temp);
                tasks[taskCount].date = temp.substr(6);
                
                getline(f, temp);
                tasks[taskCount].time = temp.substr(7);
                
                getline(f, temp);
                getline(f, temp);
                
                taskCount++;
            }
        }
        
        cout << "Загружено: " << taskCount << " задач\n";
    } else {
        cout << "Файл не найден. Начинаем с чистого листа.\n";
    }
}