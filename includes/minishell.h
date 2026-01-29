/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:37:09 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/28 22:21:38 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	RED_OUT,
	RED_IN,
	APPEND,
	HERE_DOC,
	ENV
}	t_token_type;

typedef enum e_state
{
	OUT_QUOTE,
	IN_SQUOTE,
	IN_DQUOTE
}	t_state;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_setup
{
	char	**envp;
	t_state	state;
}	t_setup;

//libft/libft.c
size_t		ft_strlen(const char *str);

//utils.c
t_token		*create_token(char *value, t_token_type type);
int			is_space(char c);
int			is_operator(char c);
void		free_tokens(t_token *head);
int			update_state(char c, int state);
char		*clean_quotes(char *str);

//lexer.c
void		add_token(t_token *new_token, t_token **head, int *i);
void		handler_redirection(char *input, t_token **head, int *i);
void		handle_word(char *input, t_token **head, int *i);
t_token		*lexer(char *input);

//expander.c
char		*append_char(char *str, char c);
char		*expand_and_join(char *new_str, char *str, int *i, t_setup env);
char		*handler_expansion(char *str, t_setup env);
void		expander(t_token *tokens, t_setup env);

//expander_utils.c
char		*extract_var_name(char *str);
void		prepare_to_split(char *var_value, int state);
char		*ft_getenv(char *name, char **env);

#endif