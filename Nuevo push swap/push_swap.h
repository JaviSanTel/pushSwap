/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:27:45 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/24 15:44:26 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "LIBFT/libft.h"
// comprobar que librerías son necesarias.

typedef struct s_stack
{
	int		content;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

//parser.c
int		is_valid_number(const char *str);
int		str_equals(const char *a, const char *b);
long	str_to_long(const char *str);
void	store_number(char *str, int *numbers, int *count, char **nbr_strs);
void	parse_tokens(char **nbr_strs, int *flag_coun, int *numbers, int *count);

//utils.c

void	error_exit(void);
void	free_split(char **arr);
void	free_all(char **nbr_strs, int *numbers);
int		has_duplicates(int *numbers, int count);
int		compute_max_size(int argc, char **argv);

//flags.c

int		get_flag_type(const char *str);
int		has_conflict(int *counts);
void	ft_init_flags(int *flag_coun);

//list_utils.c

t_stack	*new_node(int value);
t_stack	*build_list(int *numbers, int count);

//sort_simple.c

int		find_min_position(t_stack *a);
void	rotate_to_top(t_stack *a, int pos, int size);
void	sort_simple(t_stack **a, t_stack **b, int n);

//move_swap.c

void	swap(t_stack *stack);
int		swap_a(t_stack *stack);
int		swap_b(t_stack *stack);
int		swap_ss(t_stack *a, t_stack *b);

//move_push.c

void	push(t_stack **dest, t_stack **src);
int		pa(t_stack **a, t_stack **b);
int		pb(t_stack **a, t_stack **b);

//move_rotate.c

void	rotate(t_stack *stack);
int		rotate_a(t_stack *stack);
int		rotate_b(t_stack *stack);
int		rotate_rr(t_stack *a, t_stack *b);

//move_reverse_rotate.c

void	reverse_rotate(t_stack *stack);
int		reverse_rotate_a(t_stack *stack);
int		reverse_rotate_b(t_stack *stack);
int		reverse_rotate_rrr(t_stack *a, t_stack *b);

//psindex.c

int		*psindex(int *numbers, int count);

//disorder.c

double	ft_disorder(int	*numbers, int count);

//meter prototipo de las funciones.


#endif
