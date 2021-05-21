#include "ft_printf.h"

static	void	preset_float_g_f_format(t_fmt *f, t_float_cast *fc)
{
	size_t pr;

	pr = f->precision > 0 ? f->precision - 1 : 0;
	while (fc->dpart % 10 != 0 && fc->ipart == 0 \
				&& fc->dpart < (size_t)ft_pow(10, pr))
	{
		f->precision++;
		fc->dpart = (size_t)(fc->fl_dpart * 10);
	}
	pr = f->precision ? f->precision : 1;
	if (fc->ipart == 0 && fc->dpart == 0)
	{
		while (fc->fl_dpart != 0.0 && pr > 0)
		{
			fc->fl_dpart *= 10;
			if (fc->fl_dpart > 1)
				pr--;
			f->precision++;
		}
		fc->dpart = (size_t)(fc->fl_dpart + 0.5);
	}
}

static	void	set_float_g_f_format(t_fmt *f, t_float_cast *fc)
{
	t_ll	e;
	size_t	t;
	size_t	new_prec;

	preset_float_g_f_format(f, fc);
	e = fc->ipart == 0 ? 0 : get_int_len((void *)(uintptr_t)(fc->ipart));
	new_prec = e < 0 || f->precision > (size_t)e ? f->precision - e : 0;
	f->precision -= f->precision > 0 && fc->f == 0.0 ? 1 : 0;
	if (f->precision > new_prec)
	{
		t = ft_pow(10, f->precision - new_prec - 1);
		if ((size_t)fc->fl_dpart / t % 10 > 4)
			fc->dpart += (10 - (size_t)fc->fl_dpart / t % 10) * t;
		fc->ipart += fc->dpart / ft_pow(10, f->precision);
		fc->dpart /= ft_pow(10, (f->precision - new_prec));
		f->precision = new_prec;
	}
	if (fc->dpart != 0)
		while (!f->hash && fc->dpart % 10 == 0)
		{
			fc->dpart /= 10;
			f->precision > (fc->ipart == 0) && f->precision--;
		}
	else if (!f->hash)
		f->precision = 0;
}

static void		set_float_g_e_format(t_fmt *f, t_float_cast *fc, t_ll *e)
{
	size_t pr;

	pr = f->precision;
	if (fc->dpart % 10 > 4 && pr == 1 && ++fc->ipart % 10 == 0)
	{
		(*e)++;
		fc->ipart /= 10;
	}
	if (e > 0 && (size_t)e >= pr && pr == f->precision)
	{
		f->precision && f->precision--;
		fc->dpart += fc->dpart % 10 > 4 ? 10 - fc->dpart % 10 : 0;
		fc->dpart /= 10;
	}
	if (fc->dpart != 0 || f->hash)
	{
		while (!f->hash && fc->dpart % 10 == 0)
		{
			fc->dpart /= 10;
			f->precision > 1 && f->precision--;
		}
	}
	else
		f->precision = 0;
}

size_t			get_float_g_len(t_fmt f, t_float_cast *fc)
{
	t_ll			e;
	size_t			len;
	t_float_cast	mf;

	len = 0;
	f.precision = f.has_precision ? f.precision : 6;
	copy_float_cast(&mf, fc);
	mf.dpart += mf.ipart != 0 && mf.dpart % 10 > 4 ? 10 - mf.dpart % 10 : 0;
	mf.ipart += mf.dpart / ft_pow(10, f.precision);
	e = set_e_format_float(&mf, f.precision);
	if (e < -4 || (e > 0 && (size_t)e >= f.precision))
	{
		len = 5;
		set_float_g_e_format(&f, &mf, &e);
		len += f.hash || (f.precision != 0 && mf.dpart != 0);
		len += f.precision;
		return (len);
	}
	copy_float_cast(&mf, fc);
	set_float_g_f_format(&f, &mf);
	len = get_int_len((void *)(uintptr_t)(mf.ipart)) + f.precision;
	return ((len += f.precision > 0 || f.hash));
}

void			print_float_g(t_fmt *f, t_float_cast *fc)
{
	t_ll			e;
	t_float_cast	mf;

	f->precision = f->has_precision ? f->precision : 6;
	f->has_precision = 1;
	copy_float_cast(&mf, fc);
	mf.dpart += mf.ipart != 0 && mf.dpart % 10 > 4 ? 10 - mf.dpart % 10 : 0;
	mf.ipart += mf.dpart / ft_pow(10, f->precision);
	e = set_e_format_float(&mf, f->precision);
	if (e < -4 || (e > 0 && (size_t)e >= f->precision))
	{
		set_float_g_e_format(f, &mf, &e);
		print_float_f(f, &mf);
		ft_printf("e%+03d", e);
	}
	else
	{
		set_float_g_f_format(f, fc);
		print_float_f(f, fc);
	}
}
