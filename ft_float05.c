#include "ft_printf.h"

int	is_inf(double n)
{
	return (*(uint64_t *)&(n) == INF);
}

int	is_neg_inf(double n)
{
	return (*(uint64_t *)&(n) == NEG_INF);
}

int	is_nan(double n)
{
	return ((n) != (n) / 1.0);
}

int	not_num(double n)
{
	return (is_inf(n) || is_neg_inf(n) || is_nan(n));
}
