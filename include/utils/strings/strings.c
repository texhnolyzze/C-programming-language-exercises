

#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "strings.h"

#define min(a, b) a < b ? a : b

void copy(const char from[], const int fromStartIdx, char to[], const int toStartIdx, const int howMuch) {
    for (int fromIdx = fromStartIdx, toIdx = toStartIdx; fromIdx - fromStartIdx < howMuch; ++fromIdx, ++toIdx) {
        to[toIdx] = from[fromIdx];
    }
}

char *reverse(char s[]) {
    int left = 0;
    int right = strlen(s) - 1;
    char temp;
    while (left < right) {
        temp = s[left];
        s[left++] = s[right];
        s[right--] = temp;
    }
    return s;
}

char *clone(const char *src) {
    size_t len = strlen(src);
    char *clone = (char *) malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; ++i) {
        clone[i] = src[i];
    }
    clone[len] = '\0';
    return clone;
}

char *mystrcat(char *s, const char *t) {
    char *s_temp = s;
    const char *t_temp = t;
    while (*s_temp++);
    while (*t_temp++);
    s_temp--;
    t_temp--;
    while (true) {
        *s_temp-- = *t_temp--;
        if (t_temp < t) {
            break;
        }
    }
    return s;
}

bool strend(const char *s, const char *t) {
    const char *s_temp = s;
    const char *t_temp = t;
    while (*s_temp++);
    while (*t_temp++);
    s_temp--;
    t_temp--;
    if (s_temp - s < t_temp - t) {
        return false;
    }
    while (s_temp >= s && t_temp >= t) {
        if (*s_temp != *t_temp) {
            return false;
        }
        s_temp--;
        t_temp--;
    }
    return true;
}

char *mystrncpy(char *s, const char *t, size_t n) {
    char *s_temp = s;
    while (*s_temp && *t && s_temp - s < n) {
        *s_temp++ = *t++;
    }
    return s;
}

int mystrncmp(const char *s, const char *t, size_t n) {
    const char *s_temp = s;
    while (s_temp - s < n && *s_temp == *t) {
        if (!*s_temp) {
            return 0;
        }
        s_temp++;
        t++;
    }
    return s_temp - s == n ? 0 : *s_temp - *t;
}

char *mystrncat(char *s, const char *t, size_t n) {
    char *s_temp = s;
    const char *t_temp = t;
    while (*s_temp++);
    while (*t_temp++);
    s_temp--;
    t_temp--;
    const size_t s_len = s_temp - s;
    const size_t t_len = t_temp - t;
    const size_t back_offset = min((min(s_len, n)), t_len);
    s_temp -= back_offset;
    while (s_temp - s != s_len) {
        *s_temp++ = *t++;
    }
    return s;
}

int mystrcmp(const char *s1, const char *s2, bool reverse, bool case_sensitive) {
    while (*s1 == *s2 || !case_sensitive && tolower(*s1) == tolower(*s2)) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    int cmp = case_sensitive ? *s1 - *s2 : tolower(*s1) - tolower(*s2);
    if (reverse) {
        cmp = -cmp;
    }
    return cmp;
}

char *strdup_len_known(const char *src, const size_t len) {
    char *dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }
    strcpy(dst, src);
    return dst;
}
