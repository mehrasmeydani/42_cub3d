/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/26 15:54:35 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		out;
	ssize_t	j;
	int		sign;

	out = 0;
	j = -1;
	sign = 1;
	while (nptr[++j] == 32 || (nptr[j] >= 9 && nptr[j] <= 13))
		;
	if ((nptr[j] == '-' || nptr[j] == '+') && ++j)
		if (nptr[j - 1] == '-')
			sign = -1;
	while (nptr[j] >= '0' && nptr[j] <= '9')
		out = out * 10 + nptr[j++] - '0';
	return (out * sign);
}
/*
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "libft.h"

#define TEST(func, f, n) test_##n(ft_##func, func, f)

void print_test_result(const char *func_name, int passed, const char *comment)
{
    printf("%-8s: %s %s\n", func_name, passed ? "✅" : "❌", comment);
}

void test_1(int (*ft)(int), int (*f)(int), char *name) {
    int passed = 1;
    for (int c = -1; c <= 255; c++) {
        if ((!!f(c)) != !!ft(c)) {
            passed = 0;
            break;
        }
    }
    print_test_result(name, passed, "");
}

void test_2(size_t (*ft)(char *), size_t (*f)(char *), char *name) {
    int passed = 1;
    char    *test = "abc";
    char    *test2 = "";
    if (f(test) != ft(test2))
        passed = 0;
    if (f(test2) != ft(test2))
        passed = 0;
    print_test_result(name, passed, "");
}

void test3(void *(*f)(void *, int, size_t), void *(*f)(void *, int, size_t),
char *name) {
    int passed = 1;
    char    *ft_test = malloc(30);
    char    *test = malloc(30);
    if (strcmp((char *)f(ft_test, '\0', 30), (char *)f(ft_test, '\0', 30)))
        passed = 0;
    print_test_result(name, passed, "");
}

int main() {
    printf("=== Testing ft_* functions ===\n\n");
    
    TEST(isalpha, "isalpha", 1);
    TEST(isdigit, "isdigit", 1);
    TEST(isalnum, "isalnum", 1);
    TEST(isascii, "isascii", 1);
    TEST(isprint, "isprint", 1);
    TEST(strlen, "strlen", 2);
    TEST(memset, "memset", 3);
    *TEST(bzero);
    TEST(memcpy);
    TEST(memmove);
    TEST(strlcpy);
    TEST(strlcat);
    TEST(toupper);
    TEST(tolower);
    TEST(strchr);
    TEST(strrchr);
    TEST(strncmp);
    TEST(memchr);
    TEST(memcmp);
    TEST(strnstr);
    TEST(atoi);
    *
   
    printf("\n=== Tests complete ===\n");
    return 0;
}*/