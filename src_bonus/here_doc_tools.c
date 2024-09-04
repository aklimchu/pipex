/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:15:44 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 15:45:37 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

int	get_delimiter(char *argv[], t_fd *fd)
{
	(*fd).delim = ft_strdup(argv[2]);
	if ((*fd).delim == 0)
		return (1);
	return (0);
}