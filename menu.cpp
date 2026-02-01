#include "menu.h"
#include "fileio.h"
#include <iostream>
#include <string>
using namespace std;

void showTask(int i) {
    cout << i + 1 << ". ";
    
    if (tasks[i].completed) {
        cout << "[V] ";
    } else {
        cout << "[ ] ";
    }
    
    cout << tasks[i].name;
    cout << " [";
    switch (tasks[i].priority) {
        case 1: cout << "Высокий"; 
        break;
        case 2: cout << "Средний"; 
        break;
        case 3: cout << "Низкий"; 
        break;
        default: cout << "Не указан"; 
        break;
    }
    cout << "]\n   " << tasks[i].desc;
    cout << "\n   " << tasks[i].date << " " << tasks[i].time << endl;
}

void showAllTasks() {
    if (taskCount == 0) { 
        cout << "Список пуст!\n"; 
        return; 
    }
    cout << "\nВСЕ ЗАДАЧИ\n";
    for (int i = 0; i < taskCount; i++) {
        showTask(i);
    }
    cout << "-----------------\n";
}

void showActiveTasks() {
    if (taskCount == 0) {
        cout << "Список пуст!\n";
        return;
    }
    
    int activeCount = 0;
    cout << "\nАКТИВНЫЕ ЗАДАЧИ\n";
    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i].completed) {
            showTask(i);
            activeCount++;
        }
    }
    
    if (activeCount == 0) {
        cout << "Все задачи выполнены!\n";
    } else {
        cout << "Всего активных: " << activeCount << "\n";
    }
    cout << "--------------------------\n";
}

void addTask() {
    if (taskCount >= MAX_TASKS) { 
        cout << "Достигнут лимит задач!\n"; 
        return; 
    }
    
    cout << "\nДОБАВЛЕНИЕ НОВОЙ ЗАДАЧИ\n";
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
    
    tasks[taskCount].completed = false;
    
    taskCount++; 
    saveToFile(); 
    cout << "Задача добавлена!\n";
}

void markTaskCompleted() {
    showAllTasks();
    if (taskCount == 0) return;
    
    cout << "Введите номер задачи для отметки (0 - отмена): ";
    int n;
    cin >> n;
    
    if (n == 0) {
        cout << "Отменено.\n";
        return;
    }
    
    if (n < 1 || n > taskCount) {
        cout << "Неверный номер!\n";
        return;
    }
    
    int index = n - 1;
    
    if (tasks[index].completed) {
        cout << "Задача уже отмечена как выполненная!\n";
        cout << "Снять отметку? (1 - да, 0 - нет): ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            tasks[index].completed = false;
            cout << "Отметка снята!\n";
        } else {
            cout << "Отменено.\n";
        }
    } else {
        tasks[index].completed = true;
        cout << "Задача отмечена как выполненная!\n";
    }
    
    saveToFile();
}

void deleteTask() {
    showAllTasks(); 
    if (taskCount == 0) return;
    
    cout << "Номер для удаления (0 - отмена): "; 
    int n; 
    cin >> n;
    
    if (n == 0) {
        cout << "Отменено.\n";
        return;
    }
    
    if (n < 1 || n > taskCount) { 
        cout << "Неверный номер!\n"; 
        return; 
    }
    
    for (int i = n - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--; 
    saveToFile(); 
    cout << "Задача удалена!\n";
}

void editTask() {
    showAllTasks(); 
    if (taskCount == 0) return;
    
    cout << "Номер для редактирования (0 - отмена): "; 
    int n; 
    cin >> n; 
    
    if (n == 0) {
        cout << "Отменено.\n";
        return;
    }
    
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
    
    saveToFile(); 
    cout << "Задача изменена!\n";
}

void searchTasks() {
    if (taskCount == 0) { 
        cout << "Нет задач для поиска!\n"; 
        return; 
    }
    
    cout << "Поиск по: 1-названию, 2-приоритету, 3-описанию, 4-дате, 5-статусу: ";
    int choice; 
    cin >> choice; 
    cin.ignore();
    
    bool found = false;
    
    switch (choice) {
        case 1: {
            cout << "Введите название: "; 
            string s; 
            getline(cin, s);
            cout << "\n--- РЕЗУЛЬТАТЫ ПОИСКА ---\n";
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].name.find(s) != string::npos) { 
                    showTask(i); 
                    found = true; 
                }
            }
            break;
        }
        case 2: {
            cout << "Введите приоритет (1-3): "; 
            int p; 
            cin >> p;
            cout << "\n--- РЕЗУЛЬТАТЫ ПОИСКА ---\n";
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].priority == p) { 
                    showTask(i); 
                    found = true; 
                }
            }
            break;
        }
        case 3: {
            cout << "Введите текст: "; 
            string s; 
            getline(cin, s);
            cout << "\nРЕЗУЛЬТАТЫ ПОИСКА\n";
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].desc.find(s) != string::npos) { 
                    showTask(i); 
                    found = true; 
                }
            }
            break;
        }
        case 4: {
            cout << "Введите дата: "; 
            string s; 
            getline(cin, s);
            cout << "\nРЕЗУЛЬТАТЫ ПОИСКА\n";
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].date == s) { 
                    showTask(i); 
                    found = true; 
                }
            }
            break;
        }
        case 5: {
            cout << "Показать: 1-выполненные, 2-невыполненные: ";
            int status;
            cin >> status;
            cout << "\nРЕЗУЛЬТАТЫ ПОИСКА\n";
            for (int i = 0; i < taskCount; i++) {
                if ((status == 1 && tasks[i].completed) || 
                    (status == 2 && !tasks[i].completed)) { 
                    showTask(i); 
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
    cout << "----------------------------\n";
}

void showTasksByPeriod() {
    if (taskCount == 0) { 
        cout << "Нет задач!\n"; 
        return; 
    }
    
    cout << "Введите дату (дд.мм.гггг): "; 
    string date; 
    cin.ignore();
    getline(cin, date);
    
    bool found = false;
    cout << "\nЗАДАЧИ НА " << date << "\n";
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].date == date) { 
            showTask(i); 
            found = true; 
        }
    }
    
    if (!found) cout << "Задачи на выбранный период не найдены!\n";
    cout << "-------------------------\n";
}

void showStatistics() {
    int completed = 0;
    int highPriority = 0;
    int mediumPriority = 0;
    int lowPriority = 0;
    int noPriority = 0;
    
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].completed) completed++;
        
        if (tasks[i].priority == 1) highPriority++;
        else if (tasks[i].priority == 2) mediumPriority++;
        else if (tasks[i].priority == 3) lowPriority++;
        else noPriority++;
    }
    
    cout << "\nСТАТИСТИКА\n";
    cout << "Всего задач: " << taskCount << "\n";
    cout << "Выполнено: " << completed << "\n";
    cout << "Осталось: " << (taskCount - completed) << "\n";
    
    if (taskCount > 0) {
        int percent = (completed * 100) / taskCount;
        cout << "Прогресс: " << percent << "%\n";
    }
    
    cout << "\nПриоритеты:\n";
    cout << "  Высокий: " << highPriority << "\n";
    cout << "  Средний: " << mediumPriority << "\n";
    cout << "  Низкий: " << lowPriority << "\n";
    if (noPriority > 0) cout << "  Без приоритета: " << noPriority << "\n";
    cout << "---------------------------\n";
}

void sortTasks() {
    if (taskCount == 0) { 
        cout << "Нет задач для сортировки!\n"; 
        return; 
    }
    
    cout << "Сортировка по: 1-приоритету, 2-дате, 3-статусу: "; 
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
                case 3:
                    if (tasks[j].completed && !tasks[j+1].completed) {
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
    
    cout << "\nЗадачи отсортированы!\n"; 
    showAllTasks();
}

void deleteAllTasks() {
    if (taskCount == 0) {
        cout << "Список и так пуст!\n";
        return;
    }
    
    cout << "\nУДАЛЕНИЕ ВСЕХ ЗАДАЧ\n";
    cout << "Вы уверены? Это удалит ВСЕ " << taskCount << " задач!\n";
    cout << "1 - Да, удалить всё\n";
    cout << "0 - Нет, отмена\n";
    cout << "Выбор: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        taskCount = 0; 
        saveToFile();   
        cout << "Все задачи удалены!\n";
    } else {
        cout << "Отменено.\n";
    }
}

void showAbout() {
    cout << "\n";
    cout << "СПИСОК ДЕЛ\n";
    cout << "Версия: 2.0\n";
    cout << "Автор: Stellarift(Филиппов Роман)\n";
    cout << "\n";
    cout << "ОПИСАНИЕ:\n";
    cout << "Эта программа помогает организовать ваши задачи,\n";
    cout << "напоминания и дела. Вы можете добавлять, удалять,\n";
    cout << "редактировать задачи, отмечать их выполненными,\n";
    cout << "искать по разным критериям и сортировать.\n";
    cout << "\n";
    cout << "ОСОБЕННОСТИ:\n";
    cout << "Хранение до 50 задач\n";
    cout << "Приоритеты: высокий/средний/низкий\n";
    cout << "Дата и время для каждой задачи\n";
    cout << "Поиск по названию, приоритету, описанию\n";
    cout << "Статистика выполнения\n";
    cout << "Автосохранение в файл\n";
    cout << "\n";
    cout << "------------------------------------\n";
    cout << "Нажмите Enter для возврата в меню...";
    
    cin.ignore();
    cin.get(); 
}

void showMenu() {
    int choice;
    
    do {
        cout << "\nСПИСОК ДЕЛ\n";
        cout << "1. Показать все задачи\n";
        cout << "2. Показать активные задачи\n";
        cout << "3. Добавить задачу\n";
        cout << "4. Отметить как выполненную\n";
        cout << "5. Удалить задачу\n";
        cout << "6. Редактировать задачу\n";
        cout << "7. Поиск задач\n";
        cout << "8. Задачи на период\n";
        cout << "9. Статистика\n";
        cout << "10. Сортировать задачи\n";
        cout << "11. Удалить все задачи\n";
        cout << "12. О программе\n";
        cout << "13. Выход\n";
        cout << "------------------------\n";
        cout << "Выберите действие: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: showAllTasks(); 
            break;
            case 2: showActiveTasks(); 
            break;
            case 3: addTask(); 
            break;
            case 4: markTaskCompleted(); 
            break;
            case 5: deleteTask(); 
            break;
            case 6: editTask(); 
            break;
            case 7: searchTasks(); 
            break;
            case 8: showTasksByPeriod(); 
            break;
            case 9: showStatistics(); 
            break;
            case 10: sortTasks(); 
            break;
            case 11: deleteAllTasks();
            break;
            case 12: showAbout();
            break;
            case 13: cout << "Выход...\n"; 
            break;
            default: cout << "Неверный выбор!\n"; 
            break;
        }
        
    } while (choice != 13);
}