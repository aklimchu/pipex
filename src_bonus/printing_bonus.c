/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:20:10 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 08:24:44 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

//The function prints an error message with needed format ("pipex: ")
//to selected file descriptor
void	printing(char *cmd, char *result, int fd)
{
	ft_putstr_fd("pipex: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(result, fd);
}

//The function prints an error message without the program name
//to selected file descriptor
void	printing_nop(char *cmd, char *result, int fd)
{
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(result, fd);
}
