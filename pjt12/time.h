int volatile Tcount;

struct task{
	void (*fun)(void *);
	char arg[8];
};

struct timer{
	int time;
	struct task task;
	struct timer *link;
};
extern struct timer *Thead;
struct timer *get_timer();
void timer_expire(void);
void insert_timer(struct task *tskp, int ms);
void tour_timer();
void free_timer();
void app_timer(char *ap);
void timer_init();
void app_time(char *ap);

