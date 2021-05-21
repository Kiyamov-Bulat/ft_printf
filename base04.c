int	is_sh(const char *s, char c)
{
	return ((*(s) == 'h') && (*(s + 1) == (c)));
}

int	is_print(char c)
{
	return (0 <= (c) && (c) <= 0176);
}
