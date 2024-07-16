/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:05:01 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/16 17:44:59 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdio.h>
# include "../../libft/libft.h"

# define CONTAINER_SIZE 10

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

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	ft_free_all();

#endif
