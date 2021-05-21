#include "ft_printf.h"

void		print_uphex(t_output *out, size_t flen)
{
	size_t			x;
	char			buf[flen];
	size_t			diff;
	size_t			i;

	i = flen;
	x = (size_t)out->value;
	diff = out->len > flen ? 0 : flen - out->len;
	strset(buf, '0', diff);
	buf[--i] = uphex(x % 16);
	while ((x /= 16) > 0)
		buf[--i] = uphex(x % 16);
	ft_putstr(buf, flen);
}

void		print_address_hex(t_output *out, size_t flen)
{
	int			i;
	uintptr_t	p;

	ft_putstr("0x", 2);
	if (out->value == NULL)
	{
		putchar_ntimes('0', flen < 2 ? 0 : flen - 2);
		return ;
	}
	p = (uintptr_t)out->value;
	i = (sizeof(p) << 3) - 4;
	while (((p >> i) & 0xf) == 0)
		i -= 4;
	putchar_ntimes('0', flen > out->len ? flen - out->len : 0);
	while (i >= 0)
	{
		ft_putchar(hex(p >> i & 0xf));
		i -= 4;
	}
}

t_print_f	get_print_func(int type)
{
	if (type == 'd' || type == 'i')
		return (print_int);
	else if (type == 'x')
		return (print_hex);
	else if (type == 'X')
		return (print_uphex);
	else if (type == 'u')
		return (print_uint);
	else if (type == 'p')
		return (print_address_hex);
	else if (type == 'c' || type == '%')
		return (print_char);
	else
		return (print_str);
}

int			is_long_or_short(const char *f)
{
	if (*f == 'l' && (ft_strchr("diucxX", *(f + 1))))
		return (1);
	if (*f == 'l' && *(f + 1) == 'l' && (ft_strchr("diuxX", *(f + 2))))
		return (1);
	if (*f == 'h' && ft_strchr("diuxX", *(f + 1)))
		return (1);
	if (*f == 'h' && *(f + 1) == 'h' && ft_strchr("diuxX", *(f + 2)))
		return (1);
	return (0);
}

void		save_n(va_list ap, int n)
{
	int *buf_n;

	buf_n = va_arg(ap, int *);
	*buf_n = n;
}
