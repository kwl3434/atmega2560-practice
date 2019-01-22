typedef struct node{
	int data;
	struct node *link;
}NODE;

extern NODE *Head;
void insert_node_head(NODE *np);
void insert_node_tail(NODE *np);
void insert_node_ascn(NODE *np);
void free_node(NODE *np);
void tour_list();
void free_list();
NODE *get_node();
