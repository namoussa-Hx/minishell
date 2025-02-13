/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:16:27 by namoussa          #+#    #+#             */
/*   Updated: 2024/07/14 18:16:28 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_address(t_free **head)
{
	t_free	*temp;

	while (*head)
	{
		temp = NULL;
		temp = *head;
		*head = (*head)->next;
		free(temp->address);
		free(temp);
	}
	*head = NULL;
	rl_clear_history();
}

t_free	*newnode_free(void *content)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
	{
		perror("malloc");
		return (NULL);
	}
	new->address = content;
	new->next = NULL;
	return (new);
}

void	addback_node_free(t_free **head, t_free *new)
{
	t_free	*temp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_env_null(t_list *prog, t_parse *cmd)
{
	t_list	*env_null;

	env_null = prog;
	while (env_null)
	{
		if (ft_strncmp(env_null->content, "PATH", 4) == 0)
		{
			env_null = env_null->next;
			continue ;
		}
		else
		{
			ft_putendl_fd((char *)env_null->content, cmd->red_out);
		}
		env_null = env_null->next;
	}
}
