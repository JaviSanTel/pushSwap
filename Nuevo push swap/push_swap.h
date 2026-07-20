/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 11:27:45 by plopez-l          #+#    #+#             */
/*   Updated: 2026/07/16 14:12:16 by plopez-l         ###   ########.fr       */
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

typedef struct s_flags
{
	int	simple = 0;
	int	medium = 0;
	int complex = 0;
	int	adaptive = 0;
	int	bench = 0;
}	t_flags;



//meter prototipo de las funciones.


#endif
