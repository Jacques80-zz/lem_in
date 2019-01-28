long long	ft_atol(const char *nptr)
{
	long long	ret;
	int			neg;

	while (!(ret = 0) && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' ||
			*nptr == '\v' || *nptr == '\f' || *nptr == '\r'))
		++nptr;
	neg = (*nptr == '-') ? -1 : 1;
	nptr = (*nptr == '-' || *nptr == '+') ? nptr : nptr - 1;
	while (*(++nptr) >= '0' && *nptr <= '9')
		ret = ret * 10 + *nptr - '0';
	return (ret * neg);
}