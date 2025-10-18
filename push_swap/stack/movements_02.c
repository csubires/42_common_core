/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:43:30 by csubires          #+#    #+#             */
/*   Updated: 2024/07/04 07:29:14 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	ft_ra(t_stack **a, int show)
{
	t_stack	*tmp;

	if (ft_stk_size(*a) > 1)
	{
		tmp = *a;
		*a = ft_stk_last(*a);
		(*a)->next = tmp;
		*a = tmp->next;
		tmp->next = 0;
		ft_show_ornot("ra\n", show);
	}
}

void	ft_rb(t_stack **b, int show)
{
	t_stack	*tmp;

	if (ft_stk_size(*b) > 1)
	{
		tmp = *b;
		*b = ft_stk_last(*b);
		(*b)->next = tmp;
		*b = tmp->next;
		tmp->next = 0;
		ft_show_ornot("rb\n", show);
	}
}

void	ft_rr(t_stack **a, t_stack **b, int show)
{
	if ((ft_stk_size(*a) > 1) && (ft_stk_size(*b) > 1))
	{
		ft_ra(a, 0);
		ft_rb(b, 0);
		ft_show_ornot("rr\n", show);
	}
}

void	ft_rra(t_stack **a, int show)
{
	t_stack	*tmp;
	int		x;

	if (ft_stk_size(*a) > 1)
	{
		x = 0;
		tmp = *a;
		while ((*a)->next && ++x)
			*a = (*a)->next;
		(*a)->next = tmp;
		while (x-- > 1)
			tmp = tmp->next;
		tmp->next = 0;
		ft_show_ornot("rra\n", show);
	}
}

void	ft_rrb(t_stack **b, int show)
{
	t_stack	*tmp;
	int		x;

	if (ft_stk_size(*b) > 1)
	{
		x = 0;
		tmp = *b;
		while ((*b)->next && ++x)
			*b = (*b)->next;
		(*b)->next = tmp;
		while (x-- > 1)
			tmp = tmp->next;
		tmp->next = 0;
		ft_show_ornot("rrb\n", show);
	}
}
