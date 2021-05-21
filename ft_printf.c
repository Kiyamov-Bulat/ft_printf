#include "ft_printf.h"

static size_t		get_true_output_len(t_fmt *f, t_output *o)
{
	size_t len;

	if (f->has_precision)
	{
		if (o->type == 's')
			len = (size_t)f->precision < o->len ? \
				f->precision : o->len;
		else if (o->type == 'p')
			len = (size_t)f->precision < o->len ? \
				o->len - (f->precision == 0) : f->precision + 2;
		else
			len = (size_t)f->precision < o->len && o->value != 0 ? \
				o->len : f->precision;
	}
	else
		len = f->zero && !f->side && (size_t)f->field > o->len ? \
							f->field : o->len;
	if (ft_strchr("xX", o->type) && f->hash && o->value != 0)
		len += !f->has_precision && len >= o->len + 2 ? 0 : 2;
	if (ft_strchr("di", o->type))
		len += (t_ll)o->value < 0 && (size_t)f->precision >= o->len;
	return (len);
}

static int			print(t_fmt *f, t_output *o)
{
	size_t		len;
	t_ll		spaces;
	int			n;

	len = get_true_output_len(f, o);
	spaces = f->field - len - ((f->plus || f->space) \
				&& f->field > o->len && not_neg(o->value));
	n = spaces > 0 ? spaces : 0;
	!f->side && spaces > 0 ? putchar_ntimes(' ', spaces) : 0;
	if (ft_strchr("di", o->type) && not_neg(o->value))
	{
		if (f->plus)
			n += ft_putchar('+');
		else if (f->space)
			n += ft_putchar(' ');
		len -= (f->plus || f->space) \
			&& f->zero && f->field > o->len && !f->has_precision;
	}
	n += len;
	if (ft_strchr("xX", o->type) && f->hash && o->value != 0)
		len -= ft_putchar('0') + ft_putchar(o->type);
	get_print_func(o->type)(o, len);
	f->side && spaces > 0 ? putchar_ntimes(' ', spaces) : 0;
	return (n);
}

static int			print_formatted_output(va_list ap, t_fmt *dfmt)
{
	int			n;
	t_output	*output;

	n = 0;
	if (ft_strchr("diXxuspc%", *dfmt->next_fmt_part) \
		|| is_long_or_short(dfmt->next_fmt_part))
	{
		if ((output = newoutput(ap, dfmt)) == NULL)
			return (-1);
		if (is_l(dfmt->next_fmt_part, 'c') && !is_print((int)output->value))
		{
			free(output);
			return (-1);
		}
		n += print(dfmt, output);
		free(output);
	}
	else if (ft_strchr("feg", *dfmt->next_fmt_part))
		n += print_float(ap, dfmt);
	else
	{
		n += putchar_ntimes(' ', dfmt->field);
		dfmt->next_fmt_part && ++n ? ft_putchar(*dfmt->next_fmt_part) : 0;
	}
	return (n);
}

static int			printf_src(va_list ap, const char *fmt)
{
	int			n;
	int			t;
	t_fmt		*decoded_fmt;

	n = 0;
	while (*fmt)
	{
		if (*fmt == '%' && *(fmt + 1) != 'n')
		{
			fmt = ft_decode_format(ap, ++fmt, &decoded_fmt);
			if (decoded_fmt == NULL)
				return (-1);
			t = print_formatted_output(ap, decoded_fmt);
			free(decoded_fmt);
			if (t == -1)
				return (-1);
			n += t;
		}
		else if (*fmt == '%' && *++fmt == 'n')
			save_n(ap, n);
		else
			*fmt && ++n ? ft_putchar(*fmt) : 0;
		*fmt && fmt++;
	}
	return (n);
}

int					ft_printf(const char *fmt, ...)
{
	int		n;
	va_list ap;

	va_start(ap, fmt);
	n = printf_src(ap, fmt);
	va_end(ap);
	return (n);
}
