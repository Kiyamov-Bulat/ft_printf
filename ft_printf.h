#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "base.h"
# include "output.h"
# include <stdarg.h>
# define INF 0x7ff0000000000000
# define NEG_INF 0xfff0000000000000
# define NAN 0x7fffffffffffffff
# define DBL_ERROR 0.0000000000000001

typedef	struct
{
	int			sign;
	size_t		ipart;
	size_t		dpart;
	double		f;
	double		fl_dpart;
}				t_float_cast;
typedef void	(*t_print_f)(t_output *out, size_t flen);

int				ft_printf(const char *fmt, ...);
int				print_float(va_list ap, t_fmt *f);
void			print_int(t_output *out, size_t flen);
void			print_str(t_output *out, size_t flen);
void			print_hex(t_output *out, size_t flen);
void			print_uphex(t_output *out, size_t flen);
void			print_uint(t_output *out, size_t flen);
void			print_char(t_output *out, size_t flen);
void			print_address_hex(t_output *out, size_t flen);
void			print_float_e(t_fmt *f, t_float_cast *fc);
void			print_float_f(t_fmt *f, t_float_cast *fc);
void			print_float_g(t_fmt *f, t_float_cast *fc);
int				print_not_normal_num(double n, t_fmt *f);
void			save_n(va_list ap, int n);
void			copy_float_cast(t_float_cast *dst, t_float_cast *src);
t_ll			set_e_format_float(t_float_cast *fc, size_t prec);
size_t			get_float_g_len(t_fmt f, t_float_cast *fc);
t_print_f		get_print_func(int type);
int				is_long_or_short(const char *f);
const char		*ft_decode_format(\
					va_list ap, const char *fmt, t_fmt **decoded_fmt);

int				is_inf(double n);
int				is_neg_inf(double n);
int				is_nan(double n);
int				not_num(double n);

#endif
