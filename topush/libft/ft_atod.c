#include "libft.h"

static int	check_atod(char *s)
{
	while (*s)
	{
		if (*s == '.')
			return (1);
		else
			s++;
	}
	return (0);

}

double		ft_atod(char *str)
{
	double		nbr;
	int		i;
	double		chfr;
	static int	signe;

	nbr = (double)ft_atoi(str);
	if (!check_atod(str))
		return (nbr);
	i = 0;
	chfr = 10;
	while ((str[i] == '\n') || (str[i] == ' ') || (str[i] == '\t')
			|| (str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	signe = str[i] == '-' ? 1 : 0;
	i = ((str[i] == '-') || (str[i] == '+')) ? i + 1 : i;
	while (str[i] && str[i++] != '.');
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		nbr = nbr >= 0 && !signe ? nbr + (double)(str[i++] - 48) / chfr :
			nbr - (double)(str[i++] - 48) / chfr;
		chfr *= 10;
	}
	return (nbr);
}
