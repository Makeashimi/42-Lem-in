/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:20:28 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/23 20:07:46 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_path(t_lst *lst, char *here)
{
	t_path 		*tmp;

	if (cmp_lst(lst, here) == 1)
		return ;
	tmp = link_path(lst);
	if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(here) + 1)))
		ft_error("Malloc error");
	tmp->str = ft_strcpy(tmp->str, here);
	tmp->str[ft_strlen(here)] = '\0';
}

void	copy_path(t_lst *previous, t_lst *end)
{
	t_path	*last;
	t_path	*now;

	last = previous->path;
	now = end->path;
	while (last != NULL)
	{
		now = link_path(end);
		if (!(now->str = (char*)malloc(sizeof(char) * ft_strlen(last->str) + 1)))
			ft_error("Malloc error");
		now->str = ft_strcpy(now->str, last->str);
		now->str[ft_strlen(last->str)] = '\0';
		last = last->next;
	}
}

int		tube_len(t_pipe *pipe)
{
	t_pipe		*tmp;
	int			i;

	i = 0;
	tmp = pipe;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		check_tab_zero(t_global *global, int *tab)
{
	int		len;
	int		i;

	i = 0;
	len = tube_len(global->pipe);
	while (i < len)
	{
		if (tab[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_tab(t_pipe *pipe, t_ant *ant)
{
	int 		len;

	len = tube_len(pipe);
	if (!(ant->tab = (int*)malloc(sizeof(int) * len)))
		ft_error("Malloc error");
	tabset(ant->tab, 0, len);
}
