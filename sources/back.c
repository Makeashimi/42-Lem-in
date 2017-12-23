/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 16:29:40 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/23 22:38:21 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	edit_path(t_path *path, t_ant *ant)
{
	t_path		*tmp;

	while (path != NULL && ft_strcmp(path->str, ant->here) == 0)
	{
		tmp = path->next;
		free(path);
		path = tmp;
	}
}

void	remove_path(t_path *path, t_ant *ant)
{
	t_path		*tmp;
	t_path		*previous;
	int			test;

	test = 0;
	edit_path(path, ant);
	tmp = path;
	previous = path;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->str, ant->here) == 0)
		{
			previous->next = tmp->next;
			free(tmp);
			tmp = previous->next;
			test = 0;
		}
		if (test > 0)
			previous = previous->next;
		if (tmp != NULL)
			tmp = tmp->next;
		test++;
	}
}

char	*check_here_back(t_global *global, t_pipe *tmp, t_lst *lst, t_ant *ant)
{
	(void)global;
	if (ant->tab[ant->i] == 3)
		ant->tab[ant->i] = 0;
	else if (ant->tab[ant->i] == 0 && ft_strcmp(ant->here, ant->end) != 0 && (ft_strcmp(ant->here, tmp->s1) == 0 || ft_strcmp(ant->here, tmp->s2) == 0))
		return (ant->here);
	if (ant->tab[ant->i] == 1 && (ft_strcmp(ant->here, tmp->s1) == 0 || ft_strcmp(ant->here, tmp->s2) == 0))
	{
		remove_path(previous_lst(lst)->path, ant);
		if (ant->boucle == 1)
		{
			//if (cmp_path(global->pipe, ant) > 2)
			//	ant->boucle = 0;
			ant->tab[ant->i] = 0;
		}
		else
			ant->tab[ant->i] = 2;
		if (ft_strcmp(tmp->s1, ant->here) == 0)
			ant->here = tmp->s2;
		else
			ant->here = tmp->s1;
	}
	return (NULL);
}

void	init_boucle(t_pipe *tmp, t_ant *ant)
{
	ant->i = 0;
	while (tmp != NULL)
	{
		if (ant->tab[ant->i] == 3)
			ant->boucle = 1;
		ant->i++;
		tmp = tmp->next;
	}
}

char	*move_back(t_global *global, t_lst *lst, t_ant *ant)
{
	t_pipe		*tmp;

	ant->boucle = 0;
	init_boucle(global->pipe, ant);
	while (1)
	{
		tmp = global->pipe;
		ant->i = 0;
		while (tmp != NULL)
		{
			if (check_here_back(global, tmp, lst, ant) != NULL)
				return (ant->here);
			ant->i++;
			tmp = tmp->next;
		}
		if (check_tab_zero(global, ant->tab) != 1)
			return (ant->here);
	}
	return (ant->here);
}
