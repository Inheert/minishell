/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:12:41 by Théo              #+#    #+#             */
/*   Updated: 2024/10/12 15:12:54 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	ft_store_malloc(void *ptr)
{
	if (!ptr)
		return ;
	garbage_collector(ADD, ptr);
}

void	ft_unstore_malloc(void *ptr)
{
	if (!ptr)
		return ;
	garbage_collector(UNSTORE, ptr);
}

void	ft_free(void *ptr)
{
	garbage_collector(DELETE, ptr);
}

void	ft_free_all(void)
{
	garbage_collector(CLEAR, NULL);
}
