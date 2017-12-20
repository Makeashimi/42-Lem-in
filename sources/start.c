/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/20 23:29:49 by jcharloi         ###   ########.fr       */
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

int		cmplst(t_pathcpy *cpy, char *here)
{
	while (cpy != NULL)
	{
		if (ft_strcmp(cpy->strcpy, here) == 0)
			return (0);
		cpy = cpy->next;
	}
	return (1);
}

void	save_here(t_lst *begin, t_lst *end, char *here)
{
	t_path 		*tmp;
	t_pathcpy 	*tmpcpy;

	ft_printf("here a copier : %s\n", here);
	tmp = link_path(end);
	if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(here))))
		ft_error("Malloc error");
	tmp->str = ft_strcpy(tmp->str, here);
	tmp->str[ft_strlen(here)] = '\0';
	if (cmplst(begin->pathcpy, here) == 1)
	{
		tmpcpy = link_pathcpy(begin);
		if (!(tmpcpy->strcpy = (char*)malloc(sizeof(char) * ft_strlen(here))))
			ft_error("Malloc error");
		tmpcpy->strcpy = ft_strcpy(tmpcpy->strcpy, here);
		tmpcpy->strcpy[ft_strlen(here)] = '\0';
		ft_printf("pathcpy : %s\n", tmpcpy->strcpy);
	}
	ft_printf("path : %s\n", tmp->str);
}

void	what_inside_pathcpy(t_lst *begin, t_lst *end)
{
	t_pathcpy	*tmpcpy;
	//previous = pathcpy
	t_path 		*tmp;
	//lst = dernier maillon vide path

	if (begin->pathcpy == NULL)
		return ;
	tmpcpy = begin->pathcpy;
	tmp = end->path;
	while (tmpcpy->next != NULL)
	{
		tmp = link_path(begin);
		if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(tmpcpy->strcpy))))
			ft_error("Malloc error");
		tmp->str = ft_strcpy(tmp->str, tmpcpy->strcpy);
		tmp->str[ft_strlen(tmpcpy->strcpy)] = '\0';
		ft_printf("je copie ca : %s\n", tmpcpy->strcpy);
		tmpcpy = tmpcpy->next;
	}
	ft_printf("-------------\n");
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
			save_here(global->lst, get_previous(global->lst), here);
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

void	start_algo(t_global *global, t_ant *ant)
{
	t_lst	*tmp;
	char	*here;
	char	*double_here;
	int i = 0;

	double_here = NULL;
	here = ant->start;
	init_tab(global->pipe, ant);
	while (check_tab_zero(global, ant->tab) == 1)
	{
		tmp = link_lst(&global->lst);
		what_inside_pathcpy(global->lst, tmp);
		i = 0;
		if (double_here != NULL)
			ft_strdel(&double_here);
		while (ft_strcmp(here, ant->end) != 0)
		{
			here = search_path(global, ant, here);
			//ft_printf("here : %s et double : %s\n", here, double_here);
			if (i > 0 && ft_strcmp(here, double_here) == 0)
				break ;
			double_here = ft_strdup(here);
			i++;
		}
		//ft_printf("je suis arrivé là : %s\n", here);
		here = move_back(global, ant, here);
		//ft_printf("je redémarre de là : %s\n", here);
		ft_printf("\n");
	}

	/*while (i < 14)
	{
		ft_printf("%d\n", ant->tab[i]);
		i++;
	}*/

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