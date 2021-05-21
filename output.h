#ifndef OUTPUT_H
# define OUTPUT_H
# include "base.h"

typedef struct
{
	int		type;
	void	*value;
	size_t	len;
}			t_output;

t_output	*newoutput(va_list ap, t_fmt *fmt);
void		set_output(t_output *o, void *val, size_t (*f)(void *p));
void		set_int_output(va_list ap, t_output *o, const char *prefix);
void		set_hex_output(va_list ap, t_output *o, const char *prefix);
void		set_uint_output(va_list ap, t_output *o, const char *prefix);
size_t		get_int_len(void *p);
size_t		get_hex_len(void *p);
size_t		get_str_len(void *p);
size_t		get_paddress_len(void *p0);

#endif
