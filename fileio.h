#pragma once
#ifndef FILEIO_H
#define FILEIO_H

#include "task.h"

extern Task tasks[MAX_TASKS];
extern int taskCount;

void saveToFile();
void loadFromFile();

#endif