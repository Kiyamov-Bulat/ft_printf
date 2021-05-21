#ifndef BASE_H
# define BASE_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

typedef	long long int	t_ll;
typedef struct	s_fmt
{
	int			side;
	int			zero;
	int			plus;
	int			hash;
	int			space;
	size_t		field;
	size_t		precision;
	int			has_precision;
	const char	*next_fmt_part;
}				t_fmt;

char			*ft_strchr(const char *s, int c);
int				ft_putchar(char c);
void			ft_putstr(char *s, size_t len);
void			strset(char *s, char c, size_t len);
unsigned int	absu(int n);
t_ll			ft_pow(t_ll n, int p);
size_t			putchar_ntimes(char c, size_t n);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
int				not_neg(void *n);
int				dtoc(unsigned int n);
int				hex(unsigned int n);
int				uphex(unsigned int n);
int				is_digit(int n);
int				is_l(const char *s, char c);
int				is_ll(const char *s, char c);
int				is_sh(const char *s, char c);
int				is_print(char c);

#endif
