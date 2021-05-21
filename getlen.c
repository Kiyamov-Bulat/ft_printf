#include "output.h"

size_t	get_int_len(void *p)
{
	size_t			n;
	size_t			len;

	len = 1;
	n = (size_t)p;
	while ((n /= 10) > 0)
		len++;
	return (len);
}

size_t	get_hex_len(void *p)
{
	size_t			n;
	size_t			len;

	len = 1;
	n = (size_t)p;
	while ((n /= 16) > 0)
		len++;
	return (len);
}

size_t	get_paddress_len(void *p0)
{
	int			i;
	size_t		len;
	uintptr_t	p;

	if (p0 == NULL)
		return (3);
	len = 2;
	p = (uintptr_t)p0;
	i = (sizeof(p) << 3) - 4;
	while (((p >> i) & 0xf) == 0)
		i -= 4;
	while (i >= 0)
	{
		len++;
		i -= 4;
	}
	return (len);
}

size_t	get_str_len(void *p)
{
	size_t		len;
	const char	*s;

	len = 0;
	s = p;
	while (*s++)
		len++;
	return (len);
}
