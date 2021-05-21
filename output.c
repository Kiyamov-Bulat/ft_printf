#include "output.h"

void		set_output(t_output *o, void *val, size_t (*f)(void *p))
{
	o->value = val;
	if (f != NULL)
		o->len = f(val);
	else
		o->len = 1;
}

static void	set_str(va_list ap, t_output *o)
{
	o->value = (void *)va_arg(ap, char *);
	if (o->value != NULL)
		o->len = get_str_len(o->value);
	else
		o->len = 6;
}

t_output	*newoutput(va_list ap, t_fmt *fmt)
{
	size_t		i;
	t_output	*o;

	if ((o = (t_output *)malloc(sizeof(t_output))) == NULL)
		return (NULL);
	i = 0;
	o->type = *fmt->next_fmt_part;
	while (o->type == 'l' || o->type == 'h')
		o->type = *(fmt->next_fmt_part + ++i);
	if (o->type == 'd' || o->type == 'i')
		set_int_output(ap, o, fmt->next_fmt_part);
	else if (o->type == 'X' || o->type == 'x')
		set_hex_output(ap, o, fmt->next_fmt_part);
	else if (o->type == 'u')
		set_uint_output(ap, o, fmt->next_fmt_part);
	else if (o->type == 'p')
		set_output(o, va_arg(ap, void *), get_paddress_len);
	else if (o->type == 's')
		set_str(ap, o);
	else if (o->type == 'c')
		set_output(o, (void *)(uintptr_t)(va_arg(ap, int)), 0);
	else if (o->type == '%')
		set_output(o, (void *)(uintptr_t)('%'), 0);
	return (o);
}
