#include"time.h"
void task_init();
int task_insert(struct task *tskp);
int task_delete(struct task *tskp);
void task_cmd(void *arg);
void task_led(char *ap);
void task_tc1047a(void *arg);
void task_tc77(void *arg);
