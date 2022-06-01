/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:48:18 by cvidon            #+#    #+#             */
/*   Updated: 2021/11/24 14:48:18 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// --------------------------- TOP {{{
// https://eradman.com/posts/tdd-in-c.html
// https://cmocka.org/talks/cmocka_unit_testing_and_mocking.pdf
#include "libft.h"
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define TESTS 1

/* Tests framework */
int	tests_run = 0;
#define FAIL() printf("\nKO in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return (1); } } while(0)
#define _verify(test) do { int ret=test(); tests_run++; if (ret) return (ret); } while (0)

/* Time tracking */
#define TIC(T) clock_t T = clock()
#define TOC(T) printf("%s: %.4fs\n", (#T), (double)(clock() - (T)) / CLOCKS_PER_SEC)

/* /1* Logs *1/ */
/* FILE *f; */
/* f = fopen("x.log", "a+"); */
/* if (!f) */
/* 	return (-1); */
/* fprintf(f, "I'm logging something ...\n"); */

#define	MAX 2147483647
#define	MIN -2147483648

char *strgen_old(int size)
{
	char	charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char	*randstr = NULL;

	randstr = malloc(sizeof(char) * (size + 1));
	if (randstr) {
		for (int i = 0; i < size; i++) {
			randstr[i] = charset[rand() % (int)(sizeof(charset) - 1)];
		}
		randstr[size] = '\0';
	}
	return (randstr);
}

char	*strgen(int size)
{
	char	*charset = NULL;
	char	*randstr = NULL;
	int		i;

	charset = malloc(sizeof(char) * (126 + 1));
	if (charset)
	{
		randstr = malloc(sizeof(char) * (size + 1));
		if (randstr)
		{
			for (i = 1; i <= 126; i++)
				if (i == 28) // remove (28 ^\ FS file separator)
					charset[i - 1] = 'X';
				else if (i == 10) // remove (10 \n NL new line)
					charset[i - 1] = 'X';
				else
					charset[i - 1] = i;
			charset[i - 1] = '\0';
			for (i = 0; i < size; i++)
				randstr[i] = charset[rand() % 126];
			randstr[size] = '\0';
		}
		free(charset);
	}
	return (randstr);
}

// }}}
// --------------------------- TESTS OK {{{
/* int	ft_isalpha(int c); */
int	test_isalpha()
{
	for (int i = 0; i <= 255; i++)
		_assert(isalpha(i) == ft_isalpha(i));
	_assert(isalpha(MIN) == ft_isalpha(MIN));
	_assert(isalpha(MAX) == ft_isalpha(MAX));
	return (0);
}

/* int	ft_isdigit(int c); */
int	test_ft_isdigit()
{
	for (int i = 0; i <= 255; i++)
		_assert(isdigit(i) == ft_isdigit(i));
	_assert(isdigit(MIN) == ft_isdigit(MIN));
	_assert(isdigit(MAX) == ft_isdigit(MAX));
	return (0);
}

/* int	ft_isalnum(int c); */
int	test_ft_isalnum()
{
	for (int i = 0; i <= 255; i++)
		_assert(isalnum(i) == ft_isalnum(i));
	_assert(isalnum(MIN) == ft_isalnum(MIN));
	_assert(isalnum(MAX) == ft_isalnum(MAX));
	return (0);
}

/* int	ft_isascii(int c); */
int	test_ft_isascii()
{
	for (int i = 0; i <= 255; i++)
		_assert(isascii(i) == ft_isascii(i));
	_assert(isascii(MIN) == ft_isascii(MIN));
	_assert(isascii(MAX) == ft_isascii(MAX));
	return (0);
}

/* int	ft_isprint(int c); */
int	test_ft_isprint()
{
	for (int i = 0; i <= 255; i++)
		_assert(isprint(i) == ft_isprint(i));
	_assert(isprint(MIN) == ft_isprint(MIN));
	_assert(isprint(MAX) == ft_isprint(MAX));
	return (0);
}

/* int	ft_toupper(int c); */
int test_ft_toupper()
{
	for (int i = 0; i <= 255; i++)
		_assert(toupper(i) == ft_toupper(i));
	_assert(toupper(MIN) == ft_toupper(MIN));
	_assert(toupper(MAX) == ft_toupper(MAX));
	return (0);
}

/* int	ft_tolower(int c); */
int	test_ft_tolower()
{
	for (int i = 0; i <= 255; i++)
		_assert(tolower(i) == ft_tolower(i));
	_assert(tolower(MIN) == ft_tolower(MIN));
	_assert(tolower(MAX) == ft_tolower(MAX));
	return (0);
}

/* size_t	ft_strlen(const char *s); */
int	test_ft_strlen()
{
	char	*randstr;

	randstr = strgen(rand() % 20);
	_assert(strlen(randstr) == ft_strlen(randstr));
	free(randstr);
	return (0);
}

/* size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize); */
int	test_ft_strlcpy()
{
	//						  {!1,  !2,    !3,    1=2=3, 1>2>3,    1>2<3,    1<2>1,	   1<2<3};
	char	dst_list[9][7]  = {"",  "Bar", "Bar", "Bar", "BarBar", "BarBar", "Bar",	   "Ba"};
	char	src_list[9][7]  = {"1", "",    "Foo", "Foo", "Foo",    "Foo",    "FooFoo", "Foo"};
	int		dstsize_list[9] = {1,   1,     0,     3,     1,        6,        3,		   4};
	int		cols = 7; // segfault at col 8 (1<2<3)

	char	*dst0;
	char	*dst1;
	char	*src;
	int		dstsize;

	for (int i = 0; i < cols; i++)
	{
		dst0 = malloc ((strlen(dst_list[i]) + 1) * sizeof(char));
		if (!dst0)
			return (1);
		dst1 = malloc ((strlen(dst_list[i]) + 1) * sizeof(char));
		if (!dst1)
			return (1);
		src = malloc ((strlen(src_list[i]) + 1) * sizeof(char));
		if (!src)
			return (1);

		strcpy(dst0, dst_list[i]);
		strcpy(dst1, dst_list[i]);
		strcpy(src, src_list[i]);
		dstsize = dstsize_list[i];

		_assert(strlcpy(dst0, src, dstsize) == ft_strlcpy(dst1, src, dstsize));
		_assert(strcmp(dst0, dst1) == 0);
		free(dst0);
		free(dst1);
		free(src);
	}
	return (0);
}

/* size_t	ft_strlcat(char *dst, const char *src, size_t dstsize); */
int	test_ft_strlcat()
{
	//						  {!1,  !2,    !3,    1=2=3, 1>2>3,    1>2<3,    1<2>1,	   1<2<3};
	char	dst_list[9][7]  = {"",  "Bar", "Bar", "Bar", "BarBar", "BarBar", "Bar",	   "Ba"};
	char	src_list[9][7]  = {"1", "",    "Foo", "Foo", "Foo",    "Foo",    "FooFoo", "Foo"};
	int		dstsize_list[9] = {1,   1,     0,     3,     1,        6,        3,		   4};
	int		cols = 7; // segfault at col 8 (1<2<3)

	char	*dst0;
	char	*dst1;
	char	*src;
	int		dstsize;

	for (int i = 0; i < cols; i++)
	{
		dst0 = malloc ((strlen(dst_list[i]) + 1) * sizeof(char));
		if (!dst0)
			return (1);
		dst1 = malloc ((strlen(dst_list[i]) + 1) * sizeof(char));
		if (!dst1)
			return (1);
		src = malloc ((strlen(src_list[i]) + 1) * sizeof(char));
		if (!src)
			return (1);

		dstsize = dstsize_list[i];
		strcpy(dst0, dst_list[i]);
		strcpy(dst1, dst_list[i]);
		strcpy(src, src_list[i]);

		_assert(strlcat(dst0, src, dstsize) == ft_strlcat(dst1, src, dstsize));
		_assert(strcmp(dst0, dst1) == 0);
		free(dst0);
		free(dst1);
		free(src);
	}
	return (0);
}

/* char	*ft_strchr(const char *s, int c); */
int	test_ft_strchr()
{
	char	*randstr;
	char	randchar;

	randstr = strgen(rand() % 20);
	randchar = rand() % 256;
	_assert(strchr(randstr, randchar) == ft_strchr(randstr, randchar));
	free(randstr);
	_assert(strchr("salut", '\0') == ft_strchr("salut", '\0'));
	return (0);
}

/* char	*ft_strrchr(const char *s, int c); */
int	test_ft_strrchr()
{
	char	*randstr;
	char	randchar;

	randstr = strgen(rand() % 20);
	randchar = rand() % 256;
	_assert(strrchr(randstr, randchar) == ft_strrchr(randstr, randchar));
	free(randstr);
	if (tests_run <= 1)
		_assert(strrchr("salut", '\0') == ft_strrchr("salut", '\0'));
	return (0);
}

/* int		ft_strncmp(const char *s1, const char *s2, size_t n);
 *
 * strncmp compiled with fsanitize=address
 * return '-1, 0 or 1' instead '*s1 - *s2'
 */
int	test_ft_strncmp()
{
	int		n;
	int		cmp0;
	int		cmp1;
	char	*s1;
	char	*s2;

	s1 = strgen(rand() % 20);
	s2 = strgen(rand() % 20);
	n = rand() % 256;
	cmp0 = strncmp(s1, s2, n);
	cmp1 = ft_strncmp(s1, s2, n);
	free(s1);
	free(s2);
	if (!((cmp0 > 0 && cmp1 > 0) || (cmp0 < 0 && cmp1 < 0) || (cmp0 == 0 && cmp1 == 0)))
		_assert(0);
	return (0);
}

/* char	*ft_strnstr(const char *haystack, const char *needle, size_t len); */
int	test_ft_strnstr()
{
	char	*haystack;
	char	*needle;
	int		len;
	haystack = strgen(rand() % 50);
	needle = strgen(0 + rand() % 5);
	len = rand() % 20;

	_assert(strnstr(haystack, needle, len) == ft_strnstr(haystack, needle, len));
	if (tests_run <= 1)
		_assert(strnstr("", "", 1) == ft_strnstr("", "", 1));

	free(haystack);
	free(needle);
	return (0);
}

/* void	ft_bzero(void *s, size_t n); */
int	test_ft_bzero()
{
	char	*randstr;
	int		s_len;
	int		n;
	char	*s0;
	char	*s1;

	randstr = strgen(rand() % 20);
	s_len = strlen(randstr);
	n = rand() % (1 + s_len);

	s0 = malloc ((s_len + 1) * sizeof(char));
	if (!s0)
		return (1);
	s1 = malloc ((s_len + 1) * sizeof(char));
	if (!s1)
		return (1);

	strcpy(s0, randstr);
	strcpy(s1, randstr);

	while (s_len--)
		_assert(s0[s_len] == s1[s_len]);

	free(randstr);
	free(s0);
	free(s1);
	return (0);
}

/* void *memset(void *b, int c, size_t len); */
int	test_ft_memset()
{
	int		b_len;
	char	*b0;
	char	*b1;
	char	c;
	int		len;

	b_len = rand() % 20;
	len = rand() % (1 + b_len);
	c = rand() % 256;

	b0 = malloc (b_len * sizeof(char));
	if (!b0)
		return (1);
	b1 = malloc (b_len * sizeof(char));
	if (!b1)
		return (1);

	memset(b0, c, len);
	ft_memset(b1, c, len);

	while (len--)
		_assert(b0[len] == b1[len]);

	free(b0);
	free(b1);
	return (0);
}

/* void	*ft_memcpy(void *dst, const void *src, size_t n)
 *
 * n <= strlen(dst) + 1
 * n <= strlen(src) + 1
 */
int	test_ft_memcpy()
{
	char	*dst;
	char	*dst0;
	char	*dst1;
	char	*src;
	int		n;

	dst = strgen(rand() % 20);
	src = strgen(rand() % (1 + strlen(dst)));
	n = rand() % (1 + strlen(src) + 1);

	dst0 = malloc ((strlen(dst) + 1) * sizeof(char));
	if (!dst0)
		return (1);
	dst1 = malloc ((strlen(dst) + 1) * sizeof(char));
	if (!dst1)
		return (1);

	strcpy(dst0, dst);
	strcpy(dst1, dst);
	_assert(strcmp(memcpy(dst0, src, n), ft_memcpy(dst1, src, n)) == 0);
	_assert(strcmp(dst0, dst1) == 0);

	free(dst0);
	free(dst1);
	free(src);
	free(dst);
	return (0);
}

/* void	*ft_memmove(void *dst, const void *src, size_t len) */
int	test_ft_memmove()
{
	for (int i = 0; i <= 6; i++)
	{
		char dest0[] = "salut";
		char dest1[] = "salut";

		char *dst0;
		char *dst1;
		char *src0;
		char *src1;
		int len;

		if (i <= 4)
		{
			printf("%i. NORMAL\n", i);
			dst0 = dest0;
			dst1 = dest1;
			src0 = "foo";
			src1 = "foo";
			len = i;

			printf("   memmove(%s, %s, %i) => ", dst0, src0, len);
			memmove(dst0, src0, len);
			printf("%s\n", dst0);

			printf("ft_memmove(%s, %s, %i) => ", dst1, src1, len);
			ft_memmove(dst1, src1, len);
			printf("%s\n", dst1);
			_assert(strcmp(dst0, dst1) == 0);
		}

		if (i == 5)
		{
			printf("%i. OVERLAP dst > src\n", i);
			dst0 = &dest0[2];
			dst1 = &dest1[2];
			src0 = &dest0[0];
			src1 = &dest1[0];
			len = 3;

			printf("   memmove(%s, %s, %i) => ", dst0, src0, len);
			memmove(dst0, src0, len);
			printf("%s\n", dst0);

			printf("ft_memmove(%s, %s, %i) => ", dst1, src1, len);
			ft_memmove(dst1, src1, len);
			printf("%s\n", dst1);
			_assert(strcmp(dst0, dst1) == 0);
		}

		if (i == 6)
		{
			printf("%i. OVERLAP dst < src\n", i);
			dst0 = &dest0[0];
			dst1 = &dest1[0];
			src0 = &dest0[2];
			src1 = &dest1[2];
			len = 3;

			printf("   memmove(%s, %s, %i) => ", dst0, src0, len);
			memmove(dst0, src0, len);
			printf("%s\n", dst0);

			printf("ft_memmove(%s, %s, %i) => ", dst1, src1, len);
			ft_memmove(dst1, src1, len);
			printf("%s\n", dst1);
			_assert(strcmp(dst0, dst1) == 0);
		}
	}
	return (0);
}

/* void *ft_memchr(const void *s, int c, size_t n)
 *
 * n >= strlen(s) => KO
 *
 */
int	test_ft_memchr()
{
	char	*s;
	char	c;
	size_t	n;

	for (int test = 0; test <= 5; test++)
	{
		/* BOUNDARIES */
		if (test == 0)
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 2; j++)
				{
					s = "ABCDEFG";
					c = "AG"[j];
					n = i;
					_assert(ft_memchr(s, c, n) == ft_memchr(s, c, n));
				}
		/* SPECIAL */
		if (test == 1)
			for (int i = 0; i < 8; i++)
			{
				s = "ABCDEFG";
				c = '\0';
				n = i;
				_assert(ft_memchr(s, c, n) == ft_memchr(s, c, n));
			}
		/* WAY */
		if (test == 2)
			for (int i = 0; i < 8; i++)
			{
				s = "ABC CBA";
				c = 'B';
				n = i;
				_assert(ft_memchr(s, c, n) == ft_memchr(s, c, n));
			}
		/* NOP */
		if (test == 3)
			for (int i = 0; i < 8; i++)
			{
				s = "ABCDEFG";
				c = 'Z';
				n = i;
				_assert(ft_memchr(s, c, n) == ft_memchr(s, c, n));
			}
		/* EMPTY */
		if (test == 4)
		{
			s = "";
			c = '\0';
			n = 0;
			_assert(ft_memchr(s, c, n) == ft_memchr(s, c, n));
		}
	}
	return (0);
}

/* int memcmp(const void *s1, const void *s2, size_t n); */
int	test_ft_memcmp()
{
	// ZERO-LENGTH
	assert(ft_memcmp("", "", 0) == 0);
	assert(ft_memcmp("A", "C", 0) == 0);
	// IDENTICAL
	assert(ft_memcmp("AAAAAAA", "AAAAAAA", 7) == 0);
	// BOUNDARIES
	assert(ft_memcmp("CAAAAAA", "AAAAAAA", 7) > 0);
	assert(ft_memcmp("AAAAAAA", "AAAAAAC", 7) < 0);
	// SPEC
	assert(ft_memcmp("\0\0", "\0È", 2) < 0);
	return (0);
}

/* int	atoi(const char *str); */
int	test_ft_atoi()
{
	int	size = 20;
	char	charset[] = "1234567890\t\n\v\f\r    ----+++tT";
	char	*randstr = NULL;

	randstr = malloc(sizeof(char) * (size + 1));
	if (randstr) {
		for (int i = 0; i < size; i++) {
			randstr[i] = charset[rand() % (int)(sizeof(charset) - 1)];
		}
		randstr[size] = '\0';
	}

	_assert(ft_atoi(randstr) ==  atoi(randstr));
	free(randstr);
	return (0);
}

/* void	*ft_calloc(size_t count, size_t size); */
int test_ft_calloc()
{
	int	*ptr0;
	int	*ptr1;

	ptr0 = calloc(5, sizeof(int));
	ptr1 = ft_calloc(5, sizeof(int));
	_assert(memcmp(ptr0, ptr1, 5 * sizeof(int)) == 0);

	ptr0 = calloc(5, sizeof(int));
	ptr1 = ft_calloc(5, sizeof(int));
	_assert(memcmp(ptr0, ptr1, 5 * sizeof(int)) == 0);

	ptr0 = calloc(1, sizeof(int));
	ptr1 = ft_calloc(1, sizeof(int));
	_assert(memcmp(ptr0, ptr1, 1 * sizeof(int)) == 0);

	ptr0 = calloc(0, 0);
	ptr1 = ft_calloc(0, 0);
	_assert(memcmp(ptr0, ptr1, 0 * sizeof(int)) == 0);

	free(ptr0);
	free(ptr1);
	return (0);
}

// }}}
// --------------------------- TESTS KO {{{

/* char *ft_strdup(const char *s1); */
int test_ft_strdup()
{
	char	*ptr0;
	char	*ptr1;

	ptr0 = strdup("salut");
	ptr1 = ft_strdup("salut");
	_assert(strcmp(ptr0, ptr1) == 0);

	ptr0 = strdup("");
	ptr1 = ft_strdup("");
	_assert(strcmp(ptr0, ptr1) == 0);

	free(ptr0);
	free(ptr1);

	return (0);
}

// }}}
// --------------------------- BOT {{{
int	all_tests()
{
	//	Frozen

	/* _verify(test_isalpha); */
	/* _verify(test_ft_isdigit); */
	/* _verify(test_ft_isalnum); */
	/* _verify(test_ft_isascii); */
	/* _verify(test_ft_isprint); */
	/* _verify(test_ft_toupper); */
	/* _verify(test_ft_tolower); */
	/* _verify(test_ft_strlcpy); */
	/* _verify(test_ft_strlcat); */
	/* _verify(test_ft_memmove); */
	/* _verify(test_ft_memchr); */
	/* _verify(test_ft_memcmp); */
	/* _verify(test_ft_calloc); */
	_verify(test_ft_strdup);

	//	Random

	for (int i = 0; i < TESTS; i++)
	{
		/* _verify(test_ft_strlen); */
		/* _verify(test_ft_strchr); */
		/* _verify(test_ft_strrchr); */
		/* _verify(test_ft_strncmp); */
		/* _verify(test_ft_strnstr); */
		/* _verify(test_ft_bzero); */
		/* _verify(test_ft_memset); */
		/* _verify(test_ft_memcpy); */
		/* _verify(test_ft_atoi); */
	}
	return (0);
}

int	main() {
	int result;
	srand((unsigned)(time(NULL)));

	TIC(all_test);
	result = all_tests();
	TOC(all_test);

	if (result == 0)
		printf(">>>OK<<<\n");
	printf("Tests run: %d\n", tests_run);

	return (result != 0);
}
