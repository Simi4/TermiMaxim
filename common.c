#include "common.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void *safe_calloc(size_t size, size_t cnt)
{
	void *buf = calloc(size, cnt);

	assert(buf != NULL);
	return buf;
}

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

static size_t get_strings_count(char *buf)
{
	size_t cnt = 0;
	size_t arg_len = 0;

	while (1) {
		if (buf[0] == ' ') {
			cnt++;
			arg_len = 0;
		} else if (buf[0] != '\0') {
			arg_len++;
		} else {
			if (arg_len > 0)
				cnt++;
			break;
		}
		buf++;
	}
	return cnt;
}

char **split_string(char *buf)
{
	int strings_count = get_strings_count(buf);
	char **splitted_str = safe_calloc(strings_count + 1, sizeof(char *));
	char *tmp = buf;

	for (int i = 0; i < strings_count; i++) {
		splitted_str[i] = tmp;
		while (tmp[0] != ' ' && tmp[0] != '\0')
			tmp++;
		tmp[0] = '\0';
		tmp++;
	}
	return splitted_str;
}

void safe_wait(void)
{
	int status;

	wait(&status);
	//assert(status == EXIT_SUCCESS);
}
