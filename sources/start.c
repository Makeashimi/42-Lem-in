/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:25:47 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/03 21:09:43 by jcharloi         ###   ########.fr       */
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

void		search_path(t_ant *ant, t_global *global, t_lst *lst, char *here)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = global->pipe;
	while (ft_strcmp(tmp->s1, ant->end) != 0 && ft_strcmp(tmp->s2, ant->end) != 0)
	{
		//ft_printf("here : %s\n", here);
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
		ft_printf("tmp->s1 = {%s} tmp->s2 = {%s} here : %s\n", tmp->s1, tmp->s2, here);
	}
}

int			is_tab_zero(int *tab, t_pipe *pipe)
{
	int		len;
	int		i;

	i = 0;
	len = tube_len(pipe);
	while (i < len)
	{
		if (tab[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

int			path_len(t_path *path)
{
	int		i;

	i = 0;
	while (path != NULL)
	{
		i++;
		path = path->next;
	}
	return (i);
}

t_lst		*cmp_path(t_lst *lst)
{
	t_lst	*tmp_lst;
	t_lst	*cpy;
	int nb;
	int nb_b;

	nb_b = 0;
	nb = 2147483647;
	tmp_lst = lst;
	while (tmp_lst != NULL)
	{
		nb_b = path_len(tmp_lst->path);
		ft_printf("nb_b : %d\n", nb_b);
		if (nb_b < nb)
		{
			nb = nb_b;
			cpy = tmp_lst;
		}
		tmp_lst = tmp_lst->next;
	}
	return (cpy);
}

void		start_algo(t_global *global, t_ant *ant, t_lst *lst)
{
	t_lst	*cpy;
	char	*here;
	int		nb;
	int j = 0;

	nb = 0;
	init_tab(global->pipe, ant);
	here = ant->start;
	cpy = lst;
	while (is_tab_zero(ant->tab, global->pipe))
	{
		cpy = link_lst(&lst);
		search_path(ant, global, cpy, here);
		j = 0;
		while (j < 13)
		{
			ft_printf("tab : %d\n", ant->tab[j]);
			j++;
		}
	}
	//pas de chemins possible = ERROR
	lst = cmp_path(lst);
	while (lst->path != NULL)
	{
		ft_printf("%s\n", lst->path->str);
		lst->path = lst->path->next;
	}
}
