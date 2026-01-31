/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:37:42 by jnovais           #+#    #+#             */
/*   Updated: 2026/01/23 23:37:42 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./libft/libft.h"

typedef struct s_cmd
{
    char **argv;
}   t_cmd;

int	execute_cmd(t_cmd *cmd, char **envp);
char	*find_cmd_path(char *cmd, char **envp);

#endif
