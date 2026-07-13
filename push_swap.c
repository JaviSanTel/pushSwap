#include <limits.h>
#include <unistd.h>



int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	error_exit(void)
{
	write(2, "Error\n", 6)
	exit(1);
}

int	str_to_checked_int(const char *str)
{
	long	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + (str[i] -'0');
		if (num *sign < INT_MAX || num * sign < INT_MIN)
			error_exit();
		i++;
	}
	return ((int)(num * sign));
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	char	**nbr_strs;
	long	num;

	i = 1;
	while (i < argc)
	{
		nbr_strs = ft_split(argv[i], ' ');
		j = 0;
		while (nbr_strs[j] != NULL)
		{
			if (!is_valid_number(nbr_strs[j])
				error_exit();
			num = str_to_checked_int(nbr_strs[j]);
			j++;
		}
		j = 0;
		while (nbr_strs[j])
			free(nbr_strs[j++]);
		free(nbr_strs);
		i++;
	}
	return (0);
}
