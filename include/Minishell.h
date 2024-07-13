#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <errno.h>
#include "../include/libft.h"

typedef enum
{
	REDIR_IN,
	REDIR_HERE,
	REDIR_OUT,
	REDIR_APPEND
}		t_redir_enum;

typedef struct s_redir
{
   char *filename;
   t_redir_enum	type;
   struct s_redir *next;
} t_redir;

typedef struct s_args
{
	char *content;
	struct s_args *next;
}t_args;

typedef struct s_parse
{
  t_args	*cmd_args;
  t_redir	*redir_list;
  struct s_parse *next;
} t_parse;

typedef struct s_mini
{
	char			*line;
  t_list			*env_head;
	t_list 			*env_export;
}					t_mini;

 typedef struct s_free
 {
	 void *address;
	 struct s_free *next;
 } t_free;
 typedef struct s_global
 {
	int g_qoutes;
	int g_status;
	t_free *address;
 } t_global;

char *ft_pwd(int i);
void ft_env(t_args **env);
void ft_export(t_args **env, t_args **export_list, char *var_name, char *var_value);

#endif