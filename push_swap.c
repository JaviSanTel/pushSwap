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

int	has_duplicates(int *numbers, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (numbers[i] == numbers[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	count;
	int	max_size;
	char	**nbr_strs;
	int	*numbers;

	if (argc < 2)
		return (0);
	max_size = 0;
	i = 1;
	while (i < argc)
	{
		max_size = max_size + ft_strlen(argv[i]);
		i++;
	}
	numbers = malloc(sizeof(int) * max_size);
	if (!numbers)
		return ();
	count = 0;
	i = 1;
	while (i < argc)
	{
		nbr_strs = ft_split(argv[i], ' ');
		j = 0;
		while (nbr_strs[j] != NULL)
		{
			if (!is_valid_number(nbr_strs[j])
				error_exit();
			numbers[count] = str_to_checked_int(nbr_strs[j]);
			count++;
			j++;
		}
		j = 0;
		while (nbr_strs[j])
			free(nbr_strs[j++]);
		free(nbr_strs);
		i++;
	}
	if (has_duplicates(numbers, count))
		error_exit();
	return (0);
}
