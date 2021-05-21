#include "ft_printf.h"

static	t_ll	set_e_format_float__ipart_more_0(\
					t_float_cast *fc, size_t pr, size_t e)
{
	t_ll	t;
	size_t	init_ipart;

	init_ipart = fc->ipart;
	if (fc->dpart + (ft_pow(10, e - 1) * 5) > (size_t)ft_pow(10, pr)\
			&& fc->ipart >= 99)
	{
		fc->dpart += 10 - fc->dpart % 10;
		fc->ipart += pr == 0 ? ft_pow(10, e) : 0;
		e = get_int_len((void *)(uintptr_t)(++fc->ipart)) - 1;
	}
	t = ft_pow(10, e);
	fc->ipart /= t;
	if (init_ipart != fc->ipart)
	{
		if (e <= pr)
			fc->dpart = (init_ipart - fc->ipart * t) \
			* ft_pow(10, pr - e) + ((fc->dpart + 4 * t / 10) / (t));
		else
			fc->dpart = ((init_ipart - fc->ipart * t)\
			+ 5 * ft_pow(10, e - pr - 1)) / ft_pow(10, e - pr) + fc->dpart / t;
	}
	return (e);
}

static	t_ll	set_e_format_float__dpart_more_0(t_float_cast *fc, size_t pr)
{
	t_ll	t;
	size_t	e;
	size_t	dpart_len;

	dpart_len = get_int_len((void *)(uintptr_t)(fc->dpart));
	t = ft_pow(10, dpart_len - 1);
	fc->ipart = fc->dpart / t;
	e = dpart_len - pr - 1;
	fc->dpart = (fc->fl_dpart - fc->ipart * t) * ft_pow(10, -e) + 0.5;
	return (e);
}

static	t_ll	set_e_format_float__dpart_ipart_0(t_float_cast *fc, size_t pr)
{
	size_t e;

	e = -pr;
	while (((int)(fc->fl_dpart + (pr == 0 ? 0.5 : 0))) < 1\
			|| fc->fl_dpart == 0.5)
	{
		fc->fl_dpart *= 10;
		e--;
	}
	fc->ipart = (size_t)(fc->fl_dpart + (pr == 0 ? 0.5 : 0));
	fc->dpart = (size_t)((fc->fl_dpart - fc->ipart + DBL_ERROR) \
				* ft_pow(10, pr));
	return (e);
}

t_ll			set_e_format_float(t_float_cast *fc, size_t prec)
{
	t_ll e;

	e = get_int_len((void *)(uintptr_t)(fc->ipart)) - 1;
	if (fc->ipart != 0)
		e = set_e_format_float__ipart_more_0(fc, prec, e);
	else if (fc->dpart != 0)
		e = set_e_format_float__dpart_more_0(fc, prec);
	else if (fc->fl_dpart != 0.0 && fc->fl_dpart + DBL_ERROR < 1.0)
		e = set_e_format_float__dpart_ipart_0(fc, prec);
	return (e);
}

void			print_float_e(t_fmt *f, t_float_cast *fc)
{
	t_ll			e;
	t_float_cast	mf;

	copy_float_cast(&mf, fc);
	e = set_e_format_float(&mf, f->has_precision ? f->precision : 6);
	print_float_f(f, &mf);
	ft_printf("e%+03d", e);
}
