/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:29:39 by rida-cos          #+#    #+#             */
/*   Updated: 2026/02/03 21:29:58 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntax_error_message(char *token_value)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    if (token_value)
        ft_putstr_fd(token_value, 2);
    else
        ft_putstr_fd("newline", 2);
    ft_putstr_fd("'\n", 2);
}