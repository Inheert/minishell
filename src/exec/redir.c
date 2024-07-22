/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 02:47:02 by tclaereb          #+#    #+#             */
/*   Updated: 2024/07/22 04:10:42 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_ftdin(t_pipe *pipes)
{
	t_token	*tokens;
	int		fd;

	tokens = pipes->tokens;
	fd = 0;
	while (tokens)
	{
		tokens = tokens->next;
	}
}
