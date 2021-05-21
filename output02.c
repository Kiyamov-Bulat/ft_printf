#include "output.h"

static void	set_int(t_ll value, t_output *o)
{
	o->value = (void *)(uintptr_t)(value);
	o->len = get_int_len((void *)(uintptr_t)(value < 0 ? \
				-((size_t)value) : (size_t)value));
	o->len += value < 0;
}

void		set_int_output(va_list ap, t_output *o, const char *prefix)
{
	if (is_l(prefix, o->type))
		set_int(va_arg(ap, long int), o);
	else if (is_ll(prefix, o->type))
		set_int(va_arg(ap, t_ll), o);
	else
		set_int(va_arg(ap, int), o);
}

void		set_uint_output(va_list ap, t_output *o, const char *prefix)
{
	if (is_l(prefix, o->type))
		set_output(o, \
			(void *)(uintptr_t)(va_arg(ap, long unsigned int)), \
			get_int_len);
	else if (is_ll(prefix, o->type))
		set_output(o, (void *)(uintptr_t)(va_arg(ap, long long unsigned int)), \
			get_int_len);
	else
		set_output(o, \
			(void *)(uintptr_t)(va_arg(ap, unsigned int)), \
			get_int_len);
}

void		set_hex_output(va_list ap, t_output *o, const char *prefix)
{
	if (is_l(prefix, o->type))
		set_output(o, (void *)(uintptr_t)(va_arg(ap, long unsigned int)), \
		get_hex_len);
	else if (is_ll(prefix, o->type))
		set_output(o, (void *)(uintptr_t)(va_arg(ap, long long unsigned int)), \
		get_hex_len);
	else
		set_output(o, (void *)(uintptr_t)(va_arg(ap, unsigned int)), \
		get_hex_len);
}
