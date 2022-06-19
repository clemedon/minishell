Interactive mode:

1. 4yuub/main.c:

    void    sigint_handler(int sig)
    {
        g_tools.exit_status = 128 + sig;
        printf("\n");
        if (!g_tools.is_runing)
        {
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        }
    }

    void    handle_signals(void)
    {
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
    }

2. here_doc

    /*
    ** SIGINT here_doc handling.
    */

    void	ft_sigint_heredoc(int sig)
    {
        (void)sig;
        ft_putstr_fd("\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }

