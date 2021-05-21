#include "base.h"

int	hex(unsigned int x)
{
	return ((x) < 10 ? (dtoc(x)) : ('a' + (x) - 10));
}

int	uphex(unsigned int x)
{
	return ((x) < 10 ? (dtoc(x)) : ('A' + (x) - 10));
}

int	is_digit(int c)
{
	return ('0' <= (c) && (c) <= '9');
}

int	is_l(const char *s, char c)
{
	return (*(s) == 'l' && *((s) + 1) == (c));
}

int	is_ll(const char *s, char c)
{
	return (*(s) == 'l' && *((s) + 1) == 'l' && *((s) + 2) == (c));
}
