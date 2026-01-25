/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:14:49 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/25 15:14:59 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	t_state	state;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	j = 0;
	state = OUT_QUOTE;
	while (str[i])
	{
		if (state == OUT_QUOTE && str[i] == '\'')
			state = IN_SQUOTE;
		else if (state == OUT_QUOTE && str[i] == '\"')
			state = IN_DQUOTE;
		else if (state == IN_SQUOTE && str[i] == '\'')
			state = OUT_QUOTE;
		else if (state == IN_DQUOTE && str[i] == '\"')
			state = OUT_QUOTE;
		else
			new[j++] = str[i]; // Só copia se não for a aspa de controle
		i++;
	}
	new[j] = '\0';
	return (new);
}
