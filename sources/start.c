/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/21 23:11:02 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst	*get_previous(t_lst *lst)
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

void	save_here(t_lst *lst, char *here)
{
	t_path 		*tmp;

	if (cmp_lst(lst, here) == 1)
		return ;
	tmp = link_path(lst);
	if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(here) + 1)))
		ft_error("Malloc error");
	tmp->str = ft_strcpy(tmp->str, here);
	tmp->str[ft_strlen(here)] = '\0';
	tmp->next = NULL;
}


char	*search_path(t_global *global, t_ant *ant, char *here)
{
	t_pipe	*tmp;

	tmp = global->pipe;
	ant->i = 0;
	while (tmp != NULL)
	{
		if (ant->tab[ant->i] == 0 && (ft_strcmp(tmp->s1, here) == 0 || ft_strcmp(tmp->s2, here) == 0))
		{
			save_here(get_previous(global->lst), here);
			if (ft_strcmp(here, ant->end) == 0)
				return (here);
			if (ft_strcmp(tmp->s1, here) == 0)
				here = tmp->s2;
			else
				here = tmp->s1;
			ant->tab[ant->i] = 1;
		}
		ant->i++;
		tmp = tmp->next;
	}
	return (here);
}

void	remove_path(t_path *path, char *here)
{
	t_path 		*tmp;
	t_path 		*previous;
	int			test;

	test = 0;
	while (path != NULL && ft_strcmp(path->str, here) == 0)
	{
		tmp = path->next;
		free(path);
		path = tmp;
	}
	tmp = path;
	previous = path;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->str, here) == 0)
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

char	*move_back(t_global *global, t_lst *lst, t_ant *ant, char *here)
{
	t_pipe	*tmp;

	while (1)
	{
		tmp = global->pipe;
		ant->i = 0;
		while (tmp != NULL)
		{
			if (ant->tab[ant->i] == 0 && ft_strcmp(here, ant->end) != 0 && (ft_strcmp(here, tmp->s1) == 0 || ft_strcmp(here, tmp->s2) == 0))
				return (here);
			if (ant->tab[ant->i] == 1 && (ft_strcmp(here, tmp->s1) == 0 || ft_strcmp(here, tmp->s2) == 0))
			{
				remove_path(get_previous(lst)->path, here);
				ant->tab[ant->i] = 2;
				if (ft_strcmp(tmp->s1, here) == 0)
					here = tmp->s2;
				else
					here = tmp->s1;
			}
			ant->i++;
			tmp = tmp->next;
		}
		if (check_tab_zero(global, ant->tab) != 1)
			return (here);
	}
	return (here);
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

void	start_algo(t_global *global, t_ant *ant)
{
	t_lst	*tmp;
	t_lst	*previous;
	char	*here;
	char	*double_here;
	int i = 0;

	double_here = NULL;
	here = ant->start;
	init_tab(global->pipe, ant);
	tmp = link_lst(&global->lst);
	while (check_tab_zero(global, ant->tab) == 1)
	{
		i = 0;
		if (double_here != NULL)
			ft_strdel(&double_here);
		while (ft_strcmp(here, ant->end) != 0)
		{
			here = search_path(global, ant, here);
			if (i > 0 && ft_strcmp(here, double_here) == 0)
				break ;
			double_here = ft_strdup(here);
			i++;
		}
		previous = tmp;
		tmp = link_lst(&global->lst);
		copy_path(previous, tmp);
		here = move_back(global, tmp, ant, here);
		//ft_printf("\n");
	}
	tmp = global->lst;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	free(tmp->next->path);
	tmp->next->path = NULL;
	free(tmp->next);
	tmp->next = NULL;

	while (global->lst != NULL)
	{
		while (global->lst->path != NULL)
		{
			ft_printf("strcpy : %s\n", global->lst->path->str);
			global->lst->path = global->lst->path->next;
		}
		ft_printf("\n");
		global->lst = global->lst->next;
	}
}