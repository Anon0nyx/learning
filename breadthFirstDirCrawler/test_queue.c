#include <stdlib.h>
#include "queue.c"

int main(int argc, char *argv[]) {
	queue buff;
	node *temp;
	temp = malloc(sizeof(node));
	char *foo;
	char *bar;

	queueInitialize(&buff);

	bar = "test";
	enqueue(&buff, bar);

	foo = dequeue(&buff);

	printf("%s\n", foo);
}
