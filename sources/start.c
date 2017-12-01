/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:25:47 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/01 19:59:21 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	tube_len(t_pipe *pipe)
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
	return (i);
}	

void		init_tab(t_pipe *pipe, t_ant *ant)
{
	int 		len;

	len = tube_len(pipe);
	if (!(ant->tab = (int*)malloc(sizeof(int) * len)))
		ft_error("Malloc error");
	tabset(ant->tab, 0, len);
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

void		path_cpy(t_ant *ant, int i, char *here)
{
	if (ant->var == 1)
	{
		if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(here) + 1)))
			ft_error("Malloc error");
		ant->path[i] = ft_strcpy(ant->path[i], here);
		ant->path[i][ft_strlen(here)] = '\0';
	}
}

int			search_path(t_ant *ant, t_global *global, char *here)
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
			//if (ant->var == 0)
			ant->tab[ant->i] = 2;
			//else
			//	continue;
		}
		else
			//if (ant->var == 0)
			ant->tab[ant->i] = 1;
			//else
			//	ant->tab[ant->i] = 3;
		if (ft_strcmp(tmp->s1, here) == 0)
			here = tmp->s2;
		else
			here = tmp->s1;
		path_cpy(ant, i, here);
		i++;
		ft_printf("tmp->s1 = {%s} tmp->s2 = {%s} here : %s\n", tmp->s1, tmp->s2, here);
	}
	return (i);
}

void		save_path(t_ant *ant, t_global *global, int nb, char *here)
{
	int		*tab;
	int		len;
	int		i;

	i = 0;
	if (!(ant->path = (char**)malloc(sizeof(char*) * nb + 1)))
		ft_error("Malloc error");
	ant->path[nb] = NULL;
	len = tube_len(global->pipe);
	if (!(tab = (int*)malloc(sizeof(int) * len)))
		ft_error("Malloc error");
	cpy_tab(tab, ant->tab, len);
	ant->var = 1;

	//tabset(ant->tab, 0, len);

	search_path(ant, global, here);
	cpy_tab(ant->tab, tab, len);
	while (i < len)
	{
		ft_printf("%d\n", ant->tab[i]);
		i++;
	}
}

void		start_algo(t_global *global, t_ant *ant)
{
	char	*here;
	int		nb;
	int k = 0;
	//int i = 0;

	nb = 0;
	init_tab(global->pipe, ant);
	here = ant->start;
	while (k < 3)
	{
		ft_printf("tmp : \n");
		ant->var = 0;
		nb = search_path(ant, global, here);
		/*while (i < 11)
		{
			ft_printf("%d\n", ant->tab[i]);
			i++;
		}*/
		ft_printf("nb : %d ant->nb_pipe : %d\n", nb, ant->nb_pipe);
		if (nb < ant->nb_pipe)
		{
			ant->nb_pipe = nb;
			save_path(ant, global, nb, here);
		}
		nb = 0;
		while (ant->path[nb] != NULL)
		{
			ft_printf("path : %s\n", ant->path[nb]);
			nb++;
		}
		k++;
	}
	nb = 0;
	while (ant->path[nb] != NULL)
	{
		ft_printf("path : %s\n", ant->path[nb]);
		nb++;
	}
}
