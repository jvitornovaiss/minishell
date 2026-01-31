/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:57:22 by jnovais           #+#    #+#             */
/*   Updated: 2026/01/26 20:57:22 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "executor.h"

char	*get_dir(char *path, char *cmd)
{
    char	*dir;
	char	*full_path;

    dir = strtok(path, ":");
    while (dir)
	{
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path)
            return NULL;

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (access(full_path, X_OK) == 0)
            return full_path;

        free(full_path);
        dir = strtok(NULL, ":");
	}
    return NULL;
}

char	*find_cmd_path(char *cmd, char **envp)
{
    char	*path;
	char    *path_copy;
    char    *result;
    int     i;

    i = 0;
	path = NULL;
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
		{
            path = envp[i] + 5;
			break;
		}
        i++;
    }
    if (!path)
	{
        return NULL;
	}

	path_copy = strdup(path);
    if (!path_copy)
	{
        return NULL;
	}

    result = get_dir(path_copy, cmd);
    free(path_copy);
	return result;
}
