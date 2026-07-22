/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:27:45 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/22 14:35:48 by plopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
// comprobar que librerías son necesarias.

typedef struct s_list
{
	int				*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

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

t_list	*new_node(int value);
t_list	*build_list(int *numbers, int count);

//sort_simple.c

int		find_min_position(t_list *a);
void	rotate_to_top(t_list *a, int pos, int size);
void	sort_simple(t_list **a, t_list **b, int n);

//meter prototipo de las funciones.


#endif
