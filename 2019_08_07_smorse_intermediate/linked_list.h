struct Node {
	char* data;
	struct Node *next;
};

void add_node(struct Node **head, char* data);
char* get_index(int index, struct Node *head);
void delete_index(int index, struct Node *head);
void delete_list(struct Node *head);
void print_list(struct Node *head);
