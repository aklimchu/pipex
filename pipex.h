/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:31:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/21 14:34:26 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>	//perror
# include <sys/wait.h> // waitpid
# include <errno.h>

char	*ft_strjoin_new(char const *s1, char const *s2, char const *s3);
char	*check_path(char *envp[], char **param, int copy_out);
char	**check_param(char *str, int copy_out);
void	free_all(char **arr_1, char **arr_2, char *str);
int		check_error_cmd(char **param, char *path, char *name, int flag);
void	child_process_1(char **argv, char **envp, int *fd, int fd_read, int copy_out);
int		child_process_2(char **argv, char **envp, int *fd, int copy_out);
void	printing(char *cmd, char *result, int fd);

#endif /* PIPEX_H */