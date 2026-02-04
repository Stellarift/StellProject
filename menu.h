#pragma once
#ifndef MENU_H
#define MENU_H

#include "task.h"

void showTask(int i); // Показать одну задачу (вспомогательная) 
void showAllTasks(); // Показать все задачи
void addTask(); // Добавляет задачу
void deleteTask(); // Удалить одну задачу
void editTask(); // Редактировать существующую задачу
void searchTasks(); //  Поиск задач по разным критериям
void showTasksByPeriod(); // Показать задачи на конкретную дату
void sortTasks(); //  Сортировать задачи (по приоритету/дате/статусу) 
void deleteAllTasks(); // Удалить все задачи (очистить список) 
void showAbout(); //  Показать информацию о программе
void showMenu(); // Главное меню программы (управляющая функция) 

#endif
