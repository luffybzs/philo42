/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:08:05 by ayarab            #+#    #+#             */
/*   Updated: 2024/12/23 01:45:31 by ayarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_philo	*ft_lstnew(void *content)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_philo **lst, void (*del)(void *))
{
	t_philo	*contener;
	t_philo	*tmp;

	if (!lst || !del)
		return ;
	contener = *lst;
	while (contener != NULL)
	{
		(del)(contener->content);
		tmp = contener->next;
		free(contener);
		contener = tmp;
	}
	*lst = NULL;
}
