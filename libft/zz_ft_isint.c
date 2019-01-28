#include "../includes/libft.h"

int ft_isint(long long nbr)
{
	if (nbr >= INT_MIN && nbr <= INT_MAX)
		return (1);
	else
		return (0);
}