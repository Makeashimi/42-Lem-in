/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:25:47 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/29 20:29:23 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_tab(t_pipe *pipe, t_ant *ant)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = pipe;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(ant->tab = (int*)malloc(sizeof(int) * i)))
		ft_error("Malloc error");
	tabset(ant->tab, 0, i);
}

t_pipe		*tube_get_marked(t_ant *ant, t_pipe *pipe, char *str)
{
	t_pipe	*tmp;

	tmp = pipe;
	ant->i = 0;
	while (tmp != NULL)
	{
		if ((ft_strcmp(tmp->s1, str) == 0 || ft_strcmp(tmp->s2, str) == 0) &&
			ant->tab[ant->i] == 1)
			return (tmp);
		ant->i++;
		tmp = tmp->next;
	}
	return (NULL);
}

t_pipe		*tube_get(t_ant *ant, t_pipe *pipe, char *str)
{
	t_pipe	*tmp;

	tmp = pipe;
	ant->i = 0;
	while (tmp != NULL)
	{
		if ((ft_strcmp(tmp->s1, str) == 0 || ft_strcmp(tmp->s2, str) == 0) &&
			ant->tab[ant->i] == 0)
			return (tmp);
		ant->i++;
		tmp = tmp->next;
	}
	return (NULL);
}

void		start_algo(t_global *global, t_ant *ant)
{
	t_pipe	*tmp;
	char	*here;

	init_tab(global->pipe, ant);
	tmp = global->pipe;
	here = ant->start;
	while (ft_strcmp(tmp->s1, ant->end) != 0 && ft_strcmp(tmp->s2, ant->end) != 0)
	{
		tmp = tube_get(ant, global->pipe, here);
		if (tmp == NULL)
		{
			tmp = tube_get_marked(ant, global->pipe, here);
			ant->tab[ant->i] = 2;
		}
		else
			ant->tab[ant->i] = 1;
		if (ft_strcmp(tmp->s1, here) == 0)
			here = tmp->s2;
		else
			here = tmp->s1;
		ft_printf("tmp->s1 = {%s} tmp->s2 = {%s} here : %s\n", tmp->s1, tmp->s2, here);
	}
}
