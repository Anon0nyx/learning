typedef struct queue {
	int count;
	struct node *first;
	struct node *last;
} queue;

typedef struct node {
	char *dr; // CHANGE THIS TO char IF TRYING TO WORK WITH SIMPLE DATA
	struct node *next;
} node;

int queueEmpty(queue *data) { return data->count == 0; }

void queueInitialize(queue *data) {
	data->count = 0;
	data->first = NULL;
	data->last = NULL;
}

void queueAdd(queue *data, char *info) {
	node *tmp;
	tmp = malloc(sizeof(node));
	tmp->dr = info;
	tmp->next = NULL;
	if (queueEmpty(data)) {
		data->first = data->last = tmp; 
	} else {
		data->last->next = tmp;
		data->last = tmp;
	}
	data->count++;
}

node *queueRemove(queue *data) {
	if (queueEmpty(data)) {
		return NULL;
	}
	node *tmp;
	tmp = data->first;
	data->first = data->first->next;
	data->count--;
	return tmp;
}
