#include "ft_printf.h"

void	copy_float_cast(t_float_cast *dst, t_float_cast *src)
{
	dst->f = src->f;
	dst->ipart = src->ipart;
	dst->dpart = src->dpart;
	dst->fl_dpart = src->fl_dpart;
}

int		print_not_normal_num(double n, t_fmt *f)
{
	char		*w;

	w = is_inf(n) ? "inf" : "-inf";
	w = is_inf(n) && f->plus ? "+inf" : w;
	w = is_nan(n) ? "nan" : w;
	f->precision = f->has_precision ? f->precision : 4;
	f->field = f->field > get_str_len(w) ? \
				f->field - (f->space && !f->plus && is_inf(n)) : get_str_len(w);
	if (f->side)
		if (f->space && !f->plus && is_inf(n))
			return (ft_printf(" %-*.*s", f->field, f->precision, w));
		else
			return (ft_printf("%-*.*s", f->field, f->precision, w));
	else if (f->space && !f->plus && is_inf(n))
		return (ft_printf(" %*.*s", f->field, f->precision, w));
	else
		return (ft_printf("%*.*s", f->field, f->precision, w));
}

void	print_float_f(t_fmt *f, t_float_cast *mf)
{
	ft_printf("%lld", mf->ipart);
	if (f->hash \
	|| (f->has_precision && f->precision != 0) \
	|| !f->has_precision)
		ft_printf(".");
	if (!(f->has_precision && f->precision == 0))
		ft_printf("%0*lld", f->has_precision ? f->precision : 6, mf->dpart);
}
