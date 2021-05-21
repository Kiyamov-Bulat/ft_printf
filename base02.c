#include "base.h"

char			*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

unsigned int	absu(int n)
{
	return (n < 0) ? -((unsigned int)n) : (unsigned int)n;
}

t_ll			ft_pow(t_ll n, int p)
{
	t_ll res;

	res = n;
	if (p <= 0)
		return (1);
	while (--p > 0)
		res *= n;
	return (res);
}

int				not_neg(void *n)
{
	return ((t_ll)(n) >= 0);
}

int				dtoc(unsigned int n)
{
	return (n + '0');
}
