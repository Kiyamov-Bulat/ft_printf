#include "base.h"

void			ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int				ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

void			ft_putstr(char *s, size_t len)
{
	write(1, s, len);
}

void			strset(char *s, char c, size_t n)
{
	while (n-- > 0)
		*s++ = c;
}

size_t			putchar_ntimes(char c, size_t n)
{
	char	buf[n];
	size_t	i;

	i = 0;
	while (i < n)
		buf[i++] = c;
	ft_putstr(buf, n);
	return (n);
}
