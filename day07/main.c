#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAXLINE 1028
#define LINES 595
#define MIL 1000000    // for gettimeofday()

/******
 *	
 *	read in one line at a time
 *	process that line
 *
 *	PARSE BAG LINE
 *	void parse_bags(char *s)
 *	pull this info from line:
 *		bag: bags it must contain
 *
 *
 *
 * *******/

struct contains {
	char *bag_name;
	int count;
};

/****
 * bag_t is a structure that contains the bag and an array to
 * the contains struct which just contains the name and number of each
 * bag contained in the main bag
 *
 * this is just the C way to hold info that might look like this
 * in a higher-level language:
 *
 * {
 *     "wavy indigo": [
 *	       {
 *	           bag_name: "dim teal",
 *	           count: 3
 *	       },
 *	       {
 *	           bag_name: "shiny gold",
 *	           count: 2
 *	       }
 *     ]
 * }
 *
 * ***********/

typedef struct _bag {
	char *main_bag;
	struct contains sub_bags[3];
} bag_t;

// we store all the bags in here
//static bag_t all_the_bags[LINES];


// parse_bage_line: take a line of input and get a bag and what it
// contains, then add to the all_the_bags array
void parse_bag_line(char *line)
{
	// get the main bag string
	char main_bag[25];
	char s[10], t[10];
	sscanf(line, "%s %s", s, t);
	strcpy(main_bag, s);
	strcat(main_bag, " ");	// get a space between the words
	strcat(main_bag, t);

	// get the sub bags
	char *ptr = strstr(line, "contain");  // bring the pointer to 'contain'
	ptr += 8;	// move the pointer ahead to the first sub bag

	// quit working if there are no sub bags
	if (strcmp(ptr, "no other bags.\n") == 0) return;

	// get sub bags, if there are any
	int n;
	memset(s, 0, 10);
	memset(t, 0, 10);
	printf("SUB BAGS:\n");
	while (sscanf(ptr, "%d %s %s", &n, s, t) == 3) {
		// clear string variables
		printf("%d %s %s\n", n, s, t);
		memset(s, 0, 10);
		memset(t, 0, 10);
		
		ptr  = strstr(ptr, ", ");
		if (ptr == NULL) {
			break;
		} else {
			ptr += 2;
			//printf("string : %s", ptr);
			//break;
		}
	}


	// testing	
	printf("MAIN BAG:\n%s\n", main_bag);
	//printf("SECOND PART: %s", ptr);
	printf("FULL LINE:\n%s\n", line);
}


int main(void)
{
	char line_buf[MAXLINE];
	float ttime;
	struct timeval start, stop;
	
	gettimeofday(&start, NULL);

	while (fgets(line_buf, MAXLINE, stdin)) {
		// printf("%s", line_buf);
		parse_bag_line(line_buf);
	}

	gettimeofday(&stop, NULL);
	ttime = (float)(stop.tv_sec * MIL +
			stop.tv_usec -
			start.tv_sec *
			MIL - start.tv_usec)/MIL;

	printf("total time (seconds): %f\n", ttime);

	return 0;
}
