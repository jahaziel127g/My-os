#ifndef TASK_H
#define TASK_H

void task_init();
int task_create(void (*entry)(), int user_mode);
void task_switch();

#endif
