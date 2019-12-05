struct Node {
	int data;
	struct Node *next;
};

void add_node(struct Node **head, int data);
int get_index(int index, struct Node *head);
