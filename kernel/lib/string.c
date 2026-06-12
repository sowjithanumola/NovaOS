/*
 * NovaOS String Functions Implementation
 */

#include "../include/string.h"
#include "../include/types.h"

/**
 * Fill memory with byte
 */
void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;
    while (n--) {
        *p++ = (uint8_t)c;
    }
    return s;
}

/**
 * Copy memory
 */
void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

/**
 * Compare memory
 */
int memcmp(const void *s1, const void *s2, size_t n)
{
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;
    
    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}

/**
 * Copy string
 */
char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}

/**
 * Copy n characters of string
 */
char *strncpy(char *dest, const char *src, size_t n)
{
    char *d = dest;
    while (n-- && *src) {
        *d++ = *src++;
    }
    while (n--) {
        *d++ = '\0';
    }
    return dest;
}

/**
 * Compare strings
 */
int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * Compare n characters of strings
 */
int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n-- && *s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    if (n == 0) return 0;
    return *s1 - *s2;
}

/**
 * Get string length
 */
size_t strlen(const char *s)
{
    size_t len = 0;
    while (*s++) {
        len++;
    }
    return len;
}

/**
 * Concatenate strings
 */
char *strcat(char *dest, const char *src)
{
    char *d = dest;
    while (*d) {
        d++;
    }
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}
