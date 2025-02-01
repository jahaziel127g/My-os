#ifndef TASK_H
#define TASK_H

void task_init();
int task_create(void (*entry)());
void task_switch();

#endif
