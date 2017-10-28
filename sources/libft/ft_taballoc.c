/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taballoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 17:05:01 by jcharloi          #+#    #+#             */
/*   Updated: 2017/08/08 13:41:54 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_taballoc(int *ptr, int size)
{
	int		*copy;

	if (ptr == NULL)
		return ((int*)malloc(size));
	if (!(copy = (int*)malloc(size)))
		return (NULL);
	ft_memcpy(copy, ptr, size);
	ft_memdel((void**)&ptr);
	return (copy);
}
