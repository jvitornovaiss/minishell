/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 00:22:14 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/30 00:30:11 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_quote(char *str)
{
	
}

void	remove_quotes(t_token *tokens)
{
	t_token	*curr;
	char	*new_value;

	curr = tokens;
	while (curr)
	{
		if (curr->next == WORD)
		{
			new_value = remove_quote(curr->value);
			free(curr->value);
			curr->value = new_value;
		}
		curr = curr->next;
	}
}