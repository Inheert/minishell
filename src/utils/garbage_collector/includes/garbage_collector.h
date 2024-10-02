/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:05:01 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/02 18:01:19 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdio.h>
# include "../../libft/libft.h"

# define CONTAINER_SIZE 4024

typedef enum s_garbage_action
{
	ADD,
	CLEAR,
	DELETE,
	UNSTORE
}	t_garbage_action;

typedef struct s_ptr_stockage
{
	void					*ptr;
	struct s_ptr_stockage	*next;
	struct s_ptr_stockage	*prev;
}	t_ptr_stockage;

// Core function used to add / delete a ptr to the garbage or clear the garbage
void			*garbage_collector(t_garbage_action action, void *ptr);

// Garbage strucure manipulation
t_ptr_stockage	*ptr_stockage_new(void *ptr);
void			ptr_stockage_add_back(t_ptr_stockage **storage,
					t_ptr_stockage *new);
void			ptr_stockage_clear(t_ptr_stockage **storage);
unsigned int	hashf(void *ptr, int size);

// Allocation and free functions
void			*ft_malloc(size_t size);
void			ft_store_malloc(void *ptr);
void			ft_unstore_malloc(void *ptr);
void			ft_free(void *ptr);
void			ft_free_all(void);

// Function to raise when malloc error happen
void			malloc_error(void);

#endif
