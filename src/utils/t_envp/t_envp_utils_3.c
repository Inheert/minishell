/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:34 by tclaereb          #+#    #+#             */
/*   Updated: 2024/09/10 17:52:07 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*t_envp_finding(t_envp *menvp, char *name)
{
	if (!menvp || !name)
		return (NULL);
	while (menvp)
	{
		if (strcmp(menvp->name, name) == 0)
			return (menvp);
		menvp = menvp->next;
	}
	return (NULL);
}
