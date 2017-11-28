/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:25:47 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/28 19:57:01 by jcharloi         ###   ########.fr       */
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

t_pipe		*new_path(t_global *global, t_ant *ant, char *str)
{
	t_pipe	*tmp;

	tmp = global->pipe;
	ant->i = 0;
	ft_printf("str : %s\n", str);
	while (tmp != NULL)
	{
		if ((ft_strcmp(tmp->s1, str) == 0 || ft_strcmp(tmp->s2, str) == 0) &&
			ant->tab[ant->i] == 0)
			return (tmp);
		ant->i++;
		tmp = tmp->next;
	}
	ft_printf("NULL INCOMING\n");
	return (NULL);
}

void		start_algo(t_global *global, t_ant *ant)
{
	t_pipe	*tmp;
	char	*here;
	int		i;

	i = 0;
	init_tab(global->pipe, ant);
	tmp = global->pipe;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->s1, ant->start) == 0 || ft_strcmp(tmp->s2, ant->start) == 0)
			break ;
		ant->i++;
		tmp = tmp->next;
	}
	ft_printf("tmp->s1 = {%s} tmp->s2 = {%s}\n", tmp->s1, tmp->s2);
	ant->tab[ant->i] = 1;
	here = ant->start;
	while (ft_strcmp(tmp->s1, ant->end) != 0 && ft_strcmp(tmp->s2, ant->end) != 0)
	{
		if (ft_strcmp(tmp->s1, here) == 0)
		{
			here = tmp->s2;
			ft_printf("here 1: %s\n", here);
			tmp = new_path(global, ant, tmp->s2);
		}
		else
		{
			here = tmp->s1;
			ft_printf("here : %s\n", here);
			tmp = new_path(global, ant, tmp->s1);
		}
		ant->tab[ant->i] = 1;
		ft_printf("tmp->s1 = {%s} tmp->s2 = {%s}\n", tmp->s1, tmp->s2);
		i++;
	}
}
