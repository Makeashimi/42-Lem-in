/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:25:47 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/02 21:56:12 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int			search_path(t_ant *ant, t_global *global, t_lst *lst, char *here)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = global->pipe;
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
		save_path(lst, here);
		i++;
		ft_printf("tmp->s1 = {%s} tmp->s2 = {%s} here : %s\n", tmp->s1, tmp->s2, here);
	}
	return (i);
}

void		start_algo(t_global *global, t_ant *ant, t_lst *lst)
{
	t_lst	*cpy;
	char	*here;
	int		nb;
	int i = 0;

	nb = 0;
	init_tab(global->pipe, ant);
	here = ant->start;
	cpy = lst;
	while (i < 3)
	{
		cpy = link_lst(&lst);
		nb = search_path(ant, global, cpy, here);
		ft_printf("nb : %d\n", nb);
		i++;
	}
	while (lst != NULL)
	{
		while (lst->path != NULL)
		{
			ft_printf("%s\n", lst->path->str);
			lst->path = lst->path->next;
		}
		ft_printf("\n");
		lst = lst->next;
	}
}
