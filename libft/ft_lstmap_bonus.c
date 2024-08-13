/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 08:08:17 by aklimchu          #+#    #+#             */
/*   Updated: 2024/05/07 09:27:18 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;
	void	*temp_c;

	if (!lst || !f || !del)
		return ((void *) 0);
	newlst = NULL;
	while (lst)
	{
		temp_c = f(lst->content);
		temp = ft_lstnew(temp_c);
		if (temp == NULL)
		{
			del(temp_c);
			ft_lstclear(&newlst, del);
			return ((void *) 0);
		}
		ft_lstadd_back(&newlst, temp);
		lst = lst->next;
	}
	return (newlst);
}
