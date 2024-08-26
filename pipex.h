/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:31:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/26 13:48:15 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>	//perror
# include <sys/wait.h> // waitpid
# include <errno.h> // do we need?

typedef struct s_fd
{
	int		pipe[2];
	int		read;
	int		write;
	int		status;
	int		copy_out;
}				t_fd;

char	*ft_strjoin_new(char const *s1, char const *s2, char const *s3);
char	*check_path(char *envp[], char **param, int copy_out);
char	**check_param(char *str, int copy_out);
void	free_all(char **arr_1, char **arr_2, char *str);
int		check_error_cmd(char **param, char *path, char *name, int flag);
void	child_process_1(char **argv, char **envp, int *fd_pipe, int fd_read);
int		child_process_2(char **argv, char **envp, int *fd_pipe, int copy_out);
void	printing(char *cmd, char *result, int fd);
void	printing_nop(char *cmd, char *result, int fd);
int		is_directory(char *path, int copy_out);
char	*str_filter(char *str, char *set);
char	**ft_split_new(char const *s, char c, int str_num);
int		count_param(char *str);

#endif /* PIPEX_H */