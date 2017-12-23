/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 16:31:17 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/23 22:34:22 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_here_exists(t_ant *ant, int i, char *tmp_here)
{
	if (i > 0 && ft_strcmp(ant->here, tmp_here) == 0)
	{
		//superbe fonction qui check si j'ai deja un chemin coming soon
		return (1);
	}
	return (0);
}

char	*check_here(t_global *global, t_pipe *tmp, t_ant *ant, char *tmp_s)
{
	tmp_s = ant->here;
	if (ft_strcmp(ant->here, ant->end) == 0)
		return (ant->here);
	if (ft_strcmp(tmp->s1, ant->here) == 0)
		ant->here = tmp->s2;
	else
		ant->here = tmp->s1;
	if (ft_strcmp(ant->here, ant->start) == 0)
	{
		ant->tab[ant->i] = 3;
		ant->here = tmp_s;
	}
	else
	{
		save_path(previous_lst(global->lst), tmp_s);
		ant->tab[ant->i] = 1;
		if (ft_strcmp(ant->here, ant->end) == 0)
		{
			save_path(previous_lst(global->lst), ant->here);
			return (ant->here);
		}
	}
	return (NULL);
}

char	*search_path(t_global *global, t_ant *ant)
{
	t_pipe	*tmp;
	char	*tmp_s;

	tmp = global->pipe;
	ant->i = 0;
	while (tmp != NULL)
	{
		if (ant->tab[ant->i] == 0 && (ft_strcmp(tmp->s1, ant->here) == 0 || ft_strcmp(tmp->s2, ant->here) == 0))
		{
			tmp_s = ant->here;
			if (check_here(global, tmp, ant, tmp_s) != NULL)
				return (ant->here);
		}
		ant->i++;
		tmp = tmp->next;
	}
	return (ant->here);
}

void	get_paths(t_global *global, t_ant *ant)
{
	char	*tmp_here;
	t_lst	*tmp;
	t_lst	*previous;
	int		i;

	tmp = link_lst(&global->lst);
	tmp_here = NULL;
	while (check_tab_zero(global, ant->tab) == 1)
	{
		i = 0;
		if (tmp_here != NULL)
			ft_strdel(&tmp_here);
		while (ft_strcmp(ant->here, ant->end) != 0)
		{
			ant->here = search_path(global, ant);
			if (check_here_exists(ant, i, tmp_here) == 1)
				break ;
			tmp_here = ant->here;
			i++;
		}
		/*int j = 0;
		while (j < 7)
		{
			ft_printf("ant->tab : %d\n", ant->tab[j]);
			j++;
		}
		ft_printf("\n");*/
		previous = tmp;
		tmp = link_lst(&global->lst);
		copy_path(previous, tmp);
		ant->here = move_back(global, tmp, ant);
	}
}

