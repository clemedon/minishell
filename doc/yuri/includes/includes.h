/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:19:23 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/31 21:46:53 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "struct.h"
# include <stddef.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# define COMMAND_NOT_FOUND ": command not found\n"
# define PROG_NAME "Minishell"
# define PERM_DENIED ": permission denied"
# define SPEC_CHAR "~`!@#$%^&*(){}[]="
# define SPEC_CHARS "~`!@#$%^&*(){}[]=-+"
# define SPEC_UNSET ""
# define EXPAND_CHAR "' \"$=,:.*!?-#@%="
# define INFILE 1
# define OUTFILE 2
# define CMD 3
# define OPE 4
# define OPT 5
# define EXP 6

extern int	g_last_status;

#endif
