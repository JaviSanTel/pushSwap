/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiesan <javiesan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:17:46 by plopez-l          #+#    #+#             */
/*   Updated: 2026/08/03 19:02:12 by javiesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_chunkdata
{
	int	csize;
	int	clow;
}	t_chunkdata;

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
int			is_valid_number(const char *str);
int			str_equals(const char *a, const char *b);
long		str_to_long(const char *str);
void		store_number(char *str, int *num, int *count, char **nbr_strs);
void		parse_tokens(char **nbr_strs, int *flag_coun, int *num, int *count);

/* utils.c */
void		error_exit(void);
void		free_split(char **arr);
void		free_all(char **nbr_strs, int *num);
int			has_duplicates(int *num, int count);
int			compute_max_size(int argc, char **argv);

/* flags.c */
int			get_flag_type(const char *str);
int			has_conflict(int *counts);
void		ft_init_flags(int *flag_coun);
int			strategy_forced(int *flags);

/* list_utils.c */
t_stack		*new_node(int value);
t_stack		*build_list(int *num, int count);
void		free_stack(t_stack *a);
void		link_node(t_stack **head, t_stack **last, t_stack *node);

/* sort_simple.c */
int			find_min_position(t_stack *a);
void		rotate_to_top(t_stack *a, int pos, int size, int *op_counts);
void		sort_simple(t_stack **a, t_stack **b, int n, int *op_counts);

/* move_swap.c */
void		swap(t_stack *stack);
int			swap_a(t_stack *stack);
int			swap_b(t_stack *stack);
int			swap_ss(t_stack *a, t_stack *b);

/* move_push.c */
void		push(t_stack **dest, t_stack **src);
int			pa(t_stack **a, t_stack **b);
int			pb(t_stack **a, t_stack **b);

/* move_rotate.c */
void		rotate(t_stack *stack);
int			rotate_a(t_stack *stack);
int			rotate_b(t_stack *stack);
int			rotate_rr(t_stack *a, t_stack *b);

/* move_reverse_rotate.c */
void		reverse_rotate(t_stack *stack);
int			reverse_rotate_a(t_stack *stack);
int			reverse_rotate_b(t_stack *stack);
int			reverse_rotate_rrr(t_stack *a, t_stack *b);

/* Operation Methods: op_utilsa.c -- op_utilsb.c */
void		op_swap_a(t_stack *a, int *op_count);
void		op_swap_b(t_stack *b, int *op_count);
void		op_push_a(t_stack **a, t_stack **b, int *op_count);
void		op_push_b(t_stack **a, t_stack **b, int *op_count);
void		op_rotate_a(t_stack *a, int *op_count);
void		op_rotate_b(t_stack *b, int *op_count);
void		op_rev_rotate_a(t_stack *a, int *op_count);
void		op_rev_rotate_b(t_stack *b, int *op_count);

/* psindex.c */
int			*psindex(int *num, int count);
int			count_smaller(int *num, int count, int idx);

/* dispatch.c */
int			choose_strategy(int *flags, double dis);
const char	*strategy_name(int strategy);
const char	*strategy_complexity(int strategy);
double		list_disorder(t_stack *a);
const char	*op_name(int index);

/* run_sort.c */
int			*init_counts(void);
void		run_small_sort(t_stack **a, int n, int *op_counts);
void		run_strategy_sort(t_stack **a, int n, int strategy, int *op_counts);
int			*execute_sort(t_stack **a, int n, int strategy, int *flags);
void		run_and_output(t_stack **a, int *flags, int count, double dis);

/* bench.c */
int			total_from_counts(int *op_counts);
void		print_percentage(double dis);
void		print_strategy_line(int *flags, int strategy, int total);
void		print_breakdown(int *op_counts);
void		print_bench(int *flags, double dis, int *op_counts);

/* main.c */
int			*get_num(int argc, char **argv, int *flag_coun, int *count);
void		validate_num(int *flag_coun, int *num, int count);
t_stack		*prepare_stack(int *num, int count);
int			parse_all_args(int argc, char **argv, int *flag_coun, int *num);

/* radix.c */
void		sort_radix(t_stack **a, t_stack **b, int n, int *op_counts);

/* special_sort.c */
void		special_sort(t_stack **a, t_stack **b, int count, int *op_counts);
void		order_special(t_stack **a, int delay, int *op_counts);

/* chunk.c */
void		sort_chunk(t_stack **a, t_stack **b, int n, int *op_counts);
int			ft_position(t_stack *x);
int			ft_size_st(t_stack *x);

#endif
