/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesumore <jesumore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:37 by csubires          #+#    #+#             */
/*   Updated: 2024/11/30 13:27:48 by jesumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	x;
	char	*tmp_s;

	if (!s)
		return ;
	x = 0;
	tmp_s = (char *)s;
	while (x < n)
		tmp_s[x++] = '\0';
}

static void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = (void *)malloc(count * size);
	if (!mem)
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}

t_dllist	*dlist_new(void *data)
{
	t_dllist	*new_node;

	new_node = (t_dllist *)ft_calloc(1, sizeof(t_dllist));
	if (!new_node)
		return (0);
	new_node->data = data;
	new_node->next = 0;
	new_node->prev = 0;
	return (new_node);
}
