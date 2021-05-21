#include "ft_printf.h"

void	print_int(t_output *out, size_t flen)
{
	t_ll			cn;
	char			buf[flen];
	size_t			un;
	size_t			diff;
	size_t			i;

	i = flen;
	cn = (t_ll)out->value;
	diff = out->len > flen ? 0 : flen - out->len;
	if (cn < 0)
		buf[0] = '-';
	strset(buf + (cn < 0), '0', diff);
	un = (cn < 0) ? -((size_t)cn) : (size_t)cn;
	buf[--i] = dtoc(un % 10);
	while ((un /= 10) > 0)
		buf[--i] = dtoc(un % 10);
	ft_putstr(buf, flen);
}

void	print_hex(t_output *out, size_t flen)
{
	char			buf[flen];
	size_t			x;
	size_t			diff;
	size_t			i;

	i = flen;
	x = (size_t)out->value;
	diff = out->len > flen ? 0 : flen - out->len;
	strset(buf, '0', diff);
	buf[--i] = hex(x % 16);
	while ((x /= 16) > 0)
		buf[--i] = hex(x % 16);
	ft_putstr(buf, flen);
}

void	print_uint(t_output *out, size_t flen)
{
	char			buf[flen];
	size_t			un;
	size_t			diff;
	size_t			i;

	i = flen;
	un = (size_t)out->value;
	diff = out->len > flen ? 0 : flen - out->len;
	strset(buf, '0', diff);
	buf[--i] = dtoc(un % 10);
	while ((un /= 10) > 0)
		buf[--i] = dtoc(un % 10);
	ft_putstr(buf, flen);
}

void	print_str(t_output *out, size_t flen)
{
	if (out->value == NULL)
		ft_putstr("(null)", flen);
	else
	{
		putchar_ntimes('0', out->len < flen ? flen - out->len : 0);
		ft_putstr(out->value, out->len < flen ? out->len : flen);
	}
}

void	print_char(t_output *out, size_t flen)
{
	if (flen > 0)
		putchar_ntimes('0', flen - 1);
	ft_putchar((char)out->value);
}
