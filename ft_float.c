#include "ft_printf.h"

static	void	set_intpart(double d, size_t *ipart, t_fmt *f)
{
	*ipart = (size_t)d;
	if (f->has_precision && f->precision == 0)
	{
		*ipart += (d - *ipart) > 0.5;
		if (d - *ipart == 0.5)
			*ipart += ((*ipart % 2) == 0 ? 0 : 1);
	}
}

static	int		set_decpart(double d, size_t *dpart, size_t prec)
{
	size_t	t;

	*dpart = (size_t)(d + 0.5);
	if (d + 0.5 > *dpart + 1)
	{
		t = (t_ll)(d * 10);
		*dpart = t % (prec * 10);
		*dpart = *dpart + 10 - *dpart % 10;
		if (*dpart / prec > 0)
		{
			*dpart %= prec * 10;
			*dpart /= 10;
			return (0);
		}
		*dpart /= 10;
	}
	if (prec != 1 && *dpart / prec > 0)
	{
		*dpart %= prec;
		return (1);
	}
	return (0);
}

static	size_t	get_float_fmt_len(t_fmt *f, t_float_cast *mf)
{
	size_t	len;
	size_t	precision;

	len = 0;
	precision = f->has_precision ? f->precision : 6;
	if (*f->next_fmt_part == 'f')
	{
		len = get_int_len((void *)(uintptr_t)(mf->ipart)) + precision;
		len += f->hash || (f->has_precision && precision != 0) \
				|| !f->has_precision ? 1 : 0;
	}
	else if (*f->next_fmt_part == 'g')
		len = get_float_g_len(*f, mf);
	else
	{
		len = 5 + precision;
		len += f->hash || precision != 0;
	}
	return (len);
}

static	int		print_float_wrap(\
	t_fmt *f, t_float_cast *mf, void (*fp)(t_fmt *fmt, t_float_cast *mf))
{
	t_ll	spaces;
	size_t	len;

	len = get_float_fmt_len(f, mf);
	if (mf->sign == 1)
		len++;
	else
		len += (f->plus || f->space);
	spaces = f->field - len;
	if (!f->side && !f->zero && spaces > 0)
		putchar_ntimes(' ', spaces);
	if (mf->sign)
		ft_putchar('-');
	else if (f->plus)
		ft_putchar('+');
	else if (f->space)
		ft_putchar(' ');
	if (!f->side && f->zero && spaces > 0)
		putchar_ntimes('0', spaces);
	fp(f, mf);
	if (f->side && spaces > 0)
		putchar_ntimes(' ', spaces);
	return (len + (spaces > 0 ? spaces : 0));
}

int				print_float(va_list ap, t_fmt *f)
{
	double			n;
	size_t			pr;
	t_float_cast	fc;

	n = va_arg(ap, double);
	if (not_num(n))
		return (print_not_normal_num(n, f));
	fc.sign = (*(size_t *)&n >> (sizeof(*(size_t *)&n) * 8 - 1)) == 1;
	n = fc.sign ? -n : n;
	fc.f = n;
	fc.dpart = 0;
	pr = f->has_precision ? ft_pow(10, f->precision) : 1000000;
	set_intpart(n, &fc.ipart, f);
	n = (n - fc.ipart) * pr;
	fc.fl_dpart = n;
	if (*f->next_fmt_part == 'f' || n >= 1 - DBL_ERROR)
		fc.ipart += set_decpart(n, &fc.dpart, pr);
	if (*f->next_fmt_part == 'f')
		return (print_float_wrap(f, &fc, print_float_f));
	if (*f->next_fmt_part == 'e')
		return (print_float_wrap(f, &fc, print_float_e));
	return (print_float_wrap(f, &fc, print_float_g));
}
