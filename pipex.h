/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:31:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/16 09:31:01 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>	//perror
#include <sys/wait.h> // waitpid

char	*ft_strjoin_new(char const *s1, char const *s2, char const *s3);
char	*check_path(char *envp[], char *command);
char	**check_param(char *str);

#endif /* PIPEX_H */