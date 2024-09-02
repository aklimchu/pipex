/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:28:16 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:21 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	printing(char *cmd, char *result, int fd)
{
	ft_putstr_fd("pipex: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(result, fd);
}

void	printing_nop(char *cmd, char *result, int fd)
{
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(result, fd);
}