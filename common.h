#pragma once
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>


void *safe_malloc(size_t size);

void *safe_calloc(size_t size, size_t cnt);

void safe_free(void *buf);

ssize_t safe_getline(char **buf);

char **split_string(char *buf);

void safe_wait(void);
