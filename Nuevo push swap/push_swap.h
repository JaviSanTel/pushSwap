#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "LIBFT/libft.h"

typedef struct s_stack
{
	int				content;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
};

/* parser.c */
int		is_valid_number(const char *str);
int		str_equals(const char *a, const char *b);
long	str_to_long(const char *str);
void	store_number(char *str, int *numbers, int *count, char **nbr_strs);
void	parse_tokens(char **nbr_strs, int *flag_coun, int *numbers, int *count);

/* utils.c */
void	error_exit(void);
void	free_split(char **arr);
void	free_all(char **nbr_strs, int *numbers);
int		has_duplicates(int *numbers, int count);
int		compute_max_size(int argc, char **argv);

/* flags.c */
int		get_flag_type(const char *str);
int		has_conflict(int *counts);
void	ft_init_flags(int *flag_coun);

/* list_utils.c */
t_stack	*new_node(int value);
t_stack	*build_list(int *numbers, int count);

/* sort_simple.c */
int		find_min_position(t_stack *a);
void	rotate_to_top(t_stack *a, int pos, int size, int *op_counts);
void	sort_simple(t_stack **a, t_stack **b, int n, int *op_counts);

/* move_swap.c */
void	swap(t_stack *stack);
int		swap_a(t_stack *stack);
int		swap_b(t_stack *stack);
int		swap_ss(t_stack *a, t_stack *b);

/* move_push.c */
void	push(t_stack **dest, t_stack **src);
int		pa(t_stack **a, t_stack **b);
int		pb(t_stack **a, t_stack **b);

/* move_rotate.c */
void	rotate(t_stack *stack);
int		rotate_a(t_stack *stack);
int		rotate_b(t_stack *stack);
int		rotate_rr(t_stack *a, t_stack *b);

/* move_reverse_rotate.c */
void	reverse_rotate(t_stack *stack);
int		reverse_rotate_a(t_stack *stack);
int		reverse_rotate_b(t_stack *stack);
int		reverse_rotate_rrr(t_stack *a, t_stack *b);

/* psindex.c */
int		*psindex(int *numbers, int count);

/* disorder.c */
double	ft_disorder(int *numbers, int count);

/* dispatch.c */
int			choose_strategy(int *flags, double dis);
int			*execute_sort(t_stack **a, int n, int strategy);
const char	*strategy_name(int strategy);
const char	*strategy_complexity(int strategy);
double		list_disorder(t_stack *a);

/* bench.c */
int			total_from_counts(int *op_counts);
const char	*op_name(int index);
void		print_breakdown(int *op_counts);
void		print_bench(int *flags, double dis, int *op_counts);

/* main.c */
int		*get_numbers(int argc, char **argv, int *flag_coun, int *count);
void	validate_numbers(int *flag_coun, int *numbers, int count);
t_stack	*prepare_stack(int *numbers, int count);
int		parse_all_args(int argc, char **argv, int *flag_coun, int *numbers);

/* sort_chunk.c, sort_radix.c, sort_near_sorted.c (stubs, de tu compañero) */
void	sort_chunk(t_stack **a, t_stack **b, int n, int *op_counts);
void	sort_radix(t_stack **a, t_stack **b, int n, int *op_counts);
void	sort_near_sorted(t_stack **a, t_stack **b, int n, int *op_counts);

#endif
