#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 400


int main(void)
{
	char line_buf[MAXLINE];
	list_t *list = list_init();
	
	while (fgets(line_buf, MAXLINE, stdin)) {
		line_buf[strcspn(line_buf, "\n")] = 0;
		//parse(list, line_buf);
		printf("%s\n", line_buf);
	}

	return 0;
}
