#include "minishell.h"

static void     ft_end_heredoc(t_dlist *cmd)
{
        ft_putstr_fd("minishell: warning: here-document delimited by end-of-line (wanted `", 2);
        ft_putstr_fd(((t_cmd *)cmd->content)->stop_word, 2);
        ft_putendl_fd("')", 2);
}

static void     ft_here_doc(t_dlist *cmd)
{
        char    *temp;
        int             fd_file;

        fd_file = open(((t_cmd *)cmd->content)->file_in, O_CREAT | O_TRUNC | O_RDWR, 0644);
        /* if (fd_file == -1) */
        /*      ft_exit(cmd, errno, NULL); */
        while (1)
        {
                write(1, "> ", 2);
                temp = get_next_line(0);
                if (temp == NULL)
                {
                        ft_end_heredoc(cmd);
                        break;
                }
				if (ft_strlen(((t_cmd *)cmd->content)->stop_word) == (ft_strlen(temp) - 1)
					&& !(ft_strncmp(temp, ((t_cmd *)cmd->content)->stop_word, ft_strlen(temp) - 1)))
					 break;
				// EXPAND VAR DE TEMP
                write(fd_file, temp, ft_strlen(temp));
        }
        ft_free(temp);
        /* ft_close(cmd, &fd_file); */
        ((t_cmd *)cmd->content)->fd_in = open(((t_cmd *)cmd->content)->file_in, O_RDONLY);
        unlink(((t_cmd *)cmd->content)->file_in);
}



void    ft_open(t_dlist *cmd)
{
		if (((t_cmd *)cmd->content)->is_here_doc)
                ft_here_doc(cmd);
        else if (((t_cmd *)cmd->content)->file_in)
        {

                ((t_cmd *)cmd->content)->fd_in = open(((t_cmd *)cmd->content)->file_in, O_RDONLY);
                /* if (((t_cmd *)cmd->content)->fd_in == -1) */
                /*      ft_file_error(cmd, 1, errno); */
        }
        if (((t_cmd *)cmd->content)->file_out)
        {
                if (((t_cmd *)cmd->content)->type_out == 6)
                        ((t_cmd *)cmd->content)->fd_out = open(((t_cmd *)cmd->content)->file_out, O_CREAT | O_APPEND | O_RDWR, 0644);
                else if (((t_cmd *)cmd->content)->type_out == 5)
                        ((t_cmd *)cmd->content)->fd_out = open(((t_cmd *)cmd->content)->file_out, O_CREAT | O_TRUNC | O_RDWR, 0644);
        }
        /* if (((t_cmd *)cmd->content)->fd_out == -1) */
        /* { */
        /*      ft_file_error(cmd, 0, errno); */
        /*      ft_close(cmd, ((t_cmd *)cmd->content)->fd_in); */
        /*      ft_close_std(); */
        /*      exit(EXIT_FAILURE); */
        /* } */
}

