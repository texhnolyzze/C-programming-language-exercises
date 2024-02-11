//
// Created by ikarimullin on 10.01.2024.
//

#ifndef SANDBOX_ARRAYS_H
#define SANDBOX_ARRAYS_H

void copy(const char from[], int fromStartIdx, char to[], int toStartIdx, int howMuch);

char *clone(const char *src);

char *reverse(char s[]);

int mystrcmp(const char *s1, const char *s2, bool reverse, bool case_sensitive);

char *mystrcat(char *s, const char *t);

bool strend(const char *s, const char *t);

char *mystrncpy(char *s, const char *t, size_t n);

int mystrncmp(const char *s, const char *t, size_t n);

char *mystrncat(char *s, const char *t, size_t n);

#endif //SANDBOX_ARRAYS_H