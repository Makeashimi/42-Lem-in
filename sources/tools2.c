/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 16:01:43 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/23 22:33:51 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		cmp_path(t_pipe *tmp, t_ant *ant)
{
	int		i;

	i = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->s1, ant->here) == 0 || ft_strcmp(tmp->s2, ant->here) == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int		cmp_lst(t_lst *lst, char *here)
{
	t_path	*tmp;

	tmp = lst->path;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->str, here) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_lst	*previous_lst(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*previous;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	previous = tmp;
	return (previous);
}
