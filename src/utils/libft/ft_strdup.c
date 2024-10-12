/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:49:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/08 16:13:45 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_s;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	new_s = ft_calloc(len, sizeof(char));
	ft_strlcpy(new_s, s, len);
	return (new_s);
}
