/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:05:01 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:30:09 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdio.h>
# include "../../libft/libft.h"

# define CONTAINER_SIZE 4024

typedef enum	s_garbage_action
{
	ADD,
	CLEAR,
	DELETE
}	t_garbage_action;

typedef struct	s_ptr_stockage
{
	void	*ptr;
	struct s_ptr_stockage *next;
	struct s_ptr_stockage *prev;
}	t_ptr_stockage;

t_ptr_stockage	*ptr_stockage_new(void *ptr);
void			ptr_stockage_add_back(t_ptr_stockage **storage, t_ptr_stockage *new);
void			ptr_stockage_clear(t_ptr_stockage **storage);

void			*garbage_collector(t_garbage_action action, void *ptr);

void			*ft_malloc(size_t size);
void			ft_free(void *ptr);
void			ft_free_all();

void			malloc_error();

#endif
