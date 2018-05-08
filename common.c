#include "common.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


pid_t safe_fork(void)
{
	pid_t pid = fork();

	assert(pid != -1);
	return pid;
}

void safe_free(void *buf)
{
	assert(buf != NULL);
	free(buf);
}

ssize_t safe_getline(char **buf)
{
	size_t n = 0;
	ssize_t len = getline(buf, &n, stdin);

	assert(len != -1);

	if (buf[0][len - 1] == '\n')
		buf[0][len - 1] = '\0';

	return len - 1;
}

char **split_string(char *buf)
{
	size_t i = 0;
	char **splitted_str = NULL;

	char *ptr = strtok(buf, " ");
	while (ptr != NULL) {
		splitted_str = realloc(splitted_str, (i+2) * sizeof(char *));
		assert(splitted_str != NULL);
		splitted_str[i++] = ptr;
		ptr = strtok(NULL, " ");
	}

	splitted_str[i] = NULL;

	return splitted_str;
}

void safe_wait(void)
{
	int status;

	wait(&status);
	//assert(status == EXIT_SUCCESS);
}
