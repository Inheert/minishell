/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluby <cluby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:09:05 by cluby             #+#    #+#             */
/*   Updated: 2024/08/02 01:08:34 by cluby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_first_word(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while (ft_isascii(str[j]) && str[j] != ' ' && str[j] != '\t')
		j++;
	return (ft_substr(str, i, j - i));
}

char	*first_word_next_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token->next)
		return (NULL);
	free(token->str);
	tmp = tmp->next;
	return (ft_first_word(tmp->str));
}

char	*delete_first_word(char *str)
{
	char *tmp;
	int	i;

	if (!str)
		return (NULL); //error
	tmp = NULL;
	tmp = ft_strdup(str);
	i = 0;
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i++;
	while (ft_isascii(tmp[i]) && tmp[i] != ' ' && tmp[i] != '\t')
		i++;
	free(str);
	str = ft_substr(tmp, i, ft_strlen(tmp) - i);
	return(free(tmp), str);
}

t_token	*last_token(t_token *lst)
{
	t_token	*temp;
	int		last;
	int		i;

	temp = lst;
	last = token_ptr_size(temp) - 1;
	i = 0;
	while (i++ < last)
		temp = temp->next;
	return (temp);
}
