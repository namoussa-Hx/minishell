/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:52:45 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/23 10:52:46 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**conv_cmd(t_args *cmd, t_mini *prog)
{
	t_args	*cur;
	int		i;
	char	**env;
	int		count;

	i = 0;
	count = 0;
	if (cmd == NULL || prog == NULL)
		return (NULL);
	count = nbr_args(cmd);
	env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(env));
	cur = cmd;
	while (cur)
	{
		env[i] = cur->content;
		cur = cur->next;
		i++;
	}
	return (env[i] = NULL, env);
}

size_t	count_strings(const char *s, char c)
{
	size_t	nb_strings;

	nb_strings = 0;
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s != c)
		{
			while (*s != '\0' && *s != c)
				s++;
			nb_strings++;
			continue ;
		}
		s++;
	}
	return (nb_strings);
}

const char	*dup_word(char **dest, const char *src, char c)
{
	size_t	len;
	size_t	i;

	while (*src == c)
		src++;
	len = 0;
	while (src[len] != '\0' && src[len] != c)
		len++;
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (*dest == NULL)
		return (NULL);
	addback_node_free(&g_global->address, newnode_free(*dest));
	i = 0;
	while (i < len)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	src += len + 1;
	return (src);
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	size_t	nbr_strings;
	size_t	i;

	if (s == NULL)
		return (NULL);
	nbr_strings = count_strings(s, c);
	strs = (char **)malloc(sizeof(char *) * (nbr_strings + 1));
	addback_node_free(&g_global->address, newnode_free(strs));
	if (strs != NULL)
	{
		strs[nbr_strings] = NULL;
		i = 0;
		while (i < nbr_strings)
		{
			s = dup_word(strs + i, s, c);
			if (s == NULL)
			{
				break ;
			}
			i++;
		}
	}
	return (strs);
}
