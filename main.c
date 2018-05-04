#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include "common.h"


static pid_t current_pid = -1;
static int wait_proc = 1;


static void signal_handler(int signo)
{
	if (current_pid != -1) {
		assert(kill(current_pid, SIGINT) != -1);
		//printf("pid %d killed\n", current_pid);
		current_pid = -1;
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, &signal_handler);

	while (1) {
		char *buf = NULL;

		printf(">>> ");

		ssize_t len = safe_getline(&buf);

		if (len < 1) {
			safe_free(buf);
			continue;
		}

		if (strcmp(buf, "exit") == 0)
			_exit(EXIT_SUCCESS);

		if (buf[len - 1] == '&') {
			buf[len - 1] = '\0';
			wait_proc = 0;
		} else {
			wait_proc = 1;
		}

		char **user_argv = split_string(buf);

		current_pid = vfork();
		assert(current_pid != -1);

		if (current_pid == 0) {
			if (execvp(user_argv[0], user_argv) == -1)
				puts("Error with execute this arguments");
			_exit(EXIT_SUCCESS);
		} else {
			if (wait_proc) {
				safe_wait();
				current_pid = -1;
			}
		}

		safe_free(user_argv);
		safe_free(buf);
	}

	return EXIT_SUCCESS;
}
