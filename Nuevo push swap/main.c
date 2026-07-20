


#include "push_swap.h"

int parse_all_args(int argc, char **argv, int *flag_counts, int *numbers)
{
	int     i;
	int     count;
	char    **nbr_strs;

	count = 0;
	i = 1;
	while (i < argc)
	{
		nbr_strs = ft_split(argv[i], ' ');
		parse_tokens(nbr_strs, flag_counts, numbers, &count);
		free_split(nbr_strs);
		i++;
	}
	return (count);
}

int main(int argc, char **argv)
{
	int flag_counts[5];
	int *numbers;
	int count;
	t_list	*a;
	t_list	*b;

	if (argc < 2)
        	return (0);
	ft_init_flags(flag_counts);
	numbers = malloc(sizeof(int) * compute_max_size(argc, argv));
	if (!numbers)
        	return (1);
	count = parse_all_args(argc, argv, flag_counts, numbers);
	if (has_conflict(flag_counts) || has_duplicates(numbers, count))
	{
		free(numbers);
		error_exit();
    	}
	a = build_list(numbers, count);
	free(numbers);
	if (!a && count > 0)
		error_exit();
	b = NULL;
	if (count > 1)
		sort_simple(&a, &b, count);
	return (0);
}
