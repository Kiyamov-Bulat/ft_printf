#include "ft_printf.h"

static const char	*set_precision(\
	va_list ap, const char *fmt, t_fmt *decoded_fmt)
{
	int	precision;

	decoded_fmt->has_precision = 1;
	if (*fmt == '*')
	{
		++fmt;
		precision = va_arg(ap, int);
		if (precision >= 0)
			decoded_fmt->precision = precision;
		else
			decoded_fmt->has_precision = 0;
	}
	else
		while (is_digit(*fmt))
		{
			decoded_fmt->precision = decoded_fmt->precision * 10 + *fmt - '0';
			++fmt;
		}
	return (fmt);
}

static const char	*set_field(va_list ap, const char *fmt, t_fmt *decoded_fmt)
{
	int field;

	if (*fmt == '*')
	{
		fmt++;
		field = va_arg(ap, int);
		decoded_fmt->side = field < 0 ? 1 : decoded_fmt->side;
		decoded_fmt->field = absu(field);
	}
	else
		while (is_digit(*fmt))
			decoded_fmt->field = decoded_fmt->field * 10 + *fmt++ - '0';
	return (fmt);
}

static t_fmt		*newfmt(void)
{
	t_fmt *fmt;

	if ((fmt = (t_fmt *)malloc(sizeof(t_fmt))) != NULL)
	{
		fmt->side = 0;
		fmt->zero = 0;
		fmt->plus = 0;
		fmt->hash = 0;
		fmt->space = 0;
		fmt->field = 0;
		fmt->precision = 0;
		fmt->has_precision = 0;
	}
	return (fmt);
}

const char			*ft_decode_format(\
	va_list ap, const char *fmt, t_fmt **decoded_fmt)
{
	if ((*decoded_fmt = newfmt()) == NULL)
		return (NULL);
	while (1)
	{
		if (*fmt == '-')
			(*decoded_fmt)->side = 1;
		else if (*fmt == '0')
			(*decoded_fmt)->zero = 1;
		else if (*fmt == '+')
			(*decoded_fmt)->plus = 1;
		else if (*fmt == '#')
			(*decoded_fmt)->hash = 1;
		else if (*fmt == ' ')
			(*decoded_fmt)->space = 1;
		else
			break ;
		fmt++;
	}
	fmt = set_field(ap, fmt, *decoded_fmt);
	if (*fmt == '.')
		fmt = set_precision(ap, ++fmt, *decoded_fmt);
	(*decoded_fmt)->next_fmt_part = fmt;
	while (*fmt == 'l' || *fmt == 'h')
		fmt++;
	return (fmt);
}
