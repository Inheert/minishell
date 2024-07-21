/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:43:58 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/21 23:41:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set(char const *s, unsigned int start, size_t len, size_t maxsize)
{
	char	*new_s;

	if (maxsize <= len - start)
		new_s = ft_calloc(maxsize + 1, sizeof(char));
	else
		new_s = ft_calloc((len - start + 1), sizeof(char));
	if (maxsize == (size_t) - 1)
		ft_strlcpy(new_s, s + start, maxsize);
	else
		ft_strlcpy(new_s, s + start, maxsize + 1);
	return (new_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*new_s;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen || len == 0)
	{
		new_s = ft_calloc(1, sizeof(char));
		return (new_s);
	}
	return (set(s, start, slen, len));
}
