/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:43:30 by csubires          #+#    #+#             */
/*   Updated: 2024/08/16 21:08:09 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_duplicate(t_stack *a)
{
	t_stack	*tmp;

	while (a)
	{
		tmp = a->next;
		while (tmp)
		{
			if (a->nbr == tmp->nbr)
				return (1);
			tmp = tmp->next;
		}
		a = a->next;
	}
	return (0);
}

t_stack	*ft_str_parse(char *str, int *error)
{
	t_stack			*a;
	char			**tmp;
	unsigned int	x;
	long int		nbr;

	a = 0;
	x = 0;
	tmp = ft_split(str, ' ');
	while (tmp[x] && !*error)
	{
		nbr = ft_atoi_err(tmp[x++], error);
		if (nbr < MIN_INT || nbr > MAX_INT)
			*error = 1;
		ft_stk_add(&a, ft_new_node(nbr));
	}
	ft_free_split(tmp);
	return (a);
}

t_stack	*ft_parse(int argc, char *argv[])
{
	t_stack	*a;
	int		x;
	long	nbr;
	int		error;

	a = 0;
	error = 0;
	if (argc == 2)
		a = ft_str_parse(argv[1], &error);
	else
	{
		x = 1;
		while (x < argc && !error)
		{
			nbr = ft_atoi_err(argv[x++], &error);
			if (nbr < MIN_INT || nbr > MAX_INT)
				error = 1;
			ft_stk_add(&a, ft_new_node(nbr));
		}
	}
	if (error)
		ft_stk_free(&a);
	return (a);
}
