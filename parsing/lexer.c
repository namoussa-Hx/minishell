/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:51:08 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 15:51:10 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_sp(char c)
{
	return ((c == '>' || c == '<' || c == '|' || ft_isspace(c)) || c == '\t');
}

int	word_token(t_mini *prog, t_token **head, int i)
{
	char	*ptr;
	int		dflag;
	int		sflag;
	int		len;

	dflag = 0;
	sflag = 0;
	len = -1;
	while (prog->line[i + (++len)])
	{
		if (dflag == 0 && sflag == 0)
			if (prog->line[i + len] && ft_sp(prog->line[i + len]) == 1)
				break ;
		if (prog->line[i + len] == '\"' && sflag == 0)
			dflag = !dflag;
		if (prog->line[i + len] == '\'' && dflag == 0)
			sflag = !sflag;
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (-1);
	addback_node_free(&g_global->address, newnode_free(ptr));
	ft_strncpy(ptr, prog->line + i, len + 1);
	addback_node(head, create_newnode(TOKEN_WORD, ptr));
	return (len - 1);
}

void	ft_lexer(t_mini *prog, t_token **head)
{
	int	i;

	i = 0;
	while (prog->line[i])
	{
		while (ft_isspace(prog->line[i]))
			i++;
		if (prog->line[i] == '\0')
			break ;
		if (prog->line[i] == '|')
			addback_node(head, create_newnode(TOKEN_PIPE, "|"));
		else if (prog->line[i] == '>' && prog->line[i + 1] == '>' && ++i)
			addback_node(head, create_newnode(TOKEN_APPEND, ">>"));
		else if (prog->line[i] == '>' && prog->line[i + 1] != '>')
			addback_node(head, create_newnode(TOKEN_OUT, ">"));
		else if (prog->line[i] == '<' && prog->line[i + 1] == '<' && ++i)
			addback_node(head, create_newnode(TOKEN_HERE, "<<"));
		else if (prog->line[i] == '<' && prog->line[i + 1] != '<')
			addback_node(head, create_newnode(TOKEN_IN, "<"));
		else if (prog->line[i] != '\0')
			i += word_token(prog, head, i);
		i++;
	}
}

int	word_token3(t_args **args, char *str, int i, int len)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (-1);
	addback_node_free(&g_global->address, newnode_free(ptr));
	ft_strncpy(ptr, str + i, len + 1);
	if (ptr[0] == '\0')
		return (len);
	add_args_node(args, args_node(ptr));
	return (len);
}

void	word_token2(t_args **args, char *str)
{
	int	dflag;
	int	sflag;
	int	len;
	int	i;

	i = 0;
	while (str[i])
	{
		dflag = 0;
		sflag = 0;
		len = -1;
		while (str[i + (++len)])
		{
			if (dflag == 0 && sflag == 0 && ft_sp(str[i + len]))
				break ;
			if (str[i + len] == '\"' && sflag == 0)
				dflag = !dflag;
			else if (str[i + len] == '\'' && dflag == 0)
				sflag = !sflag;
		}
		word_token3(args, str, i, len);
		i += len;
		while (str[i] && ft_sp(str[i]))
			i++;
	}
}
