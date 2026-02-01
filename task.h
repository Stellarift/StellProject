#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

const int MAX_TASKS = 1000;

struct Task {
    string name;
    int priority = 0;
    string desc;
    string date;
    string time;
    bool completed = false;
};

#endif