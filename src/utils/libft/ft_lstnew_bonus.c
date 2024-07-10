/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:27:59 by tclaereb          #+#    #+#             */
/*   Updated: 2023/11/06 13:26:42 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*item;

	item = ft_calloc(1, sizeof(t_list));
	if (!item)
		return (NULL);
	item->content = content;
	item->next = NULL;
	return (item);
}
