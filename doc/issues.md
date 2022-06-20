
#           ISSUES

>       help

# //////////////////////// ATHIRION

- Fix << STOP cat << HELL cat >
> should display 'cat: cat: No such file or directory'
> error code should be 1 and not 0

# //////////////////////// CVIDON

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Comply to norm

- Fix signal heredoc SIGINT (<C-C>)
> Should send an EOF to terminate the heredoc?

- Fix SIGINT return value
> `./minishell; <C-C>; echo $?` should return 128+2 not 0.
> Is it possible without the use of a globale?

- Fix SIGQUIT and SIGINT prompt
> `$ cat<CR>salut<C-\>` shouldn't print `salut` in the prompt.
> `$ cat<CR>salut<C-C>` shouldn't print `salut` in the prompt.
> Or `$ yes<CR>salut<C-C>` shouldn't print `salut` in the prompt.

- Fix minishell with args
> './minishell salut' should display "minishell: salut: no such file
> or directory' and not simply give the prompt back (error code should
> be 127)

# //////////////////////// ???

##  Execution

##  Final

- Protect every dup2

- Close all fds that remains open

- Check every output STD
> Check that they're displayed the right STD.OUT/ERROR

- Remove tokpos
- Remove redlist

##  Wtf

- Fix execution cwd executable file
> from cwd: `touch ls; chmod +x ls; ls`
> Shouldn't print: `: Exec format error`

- Fix execution of minishell in minishell after chmod
> chmod 000 minishell
> Shouldn't print : 'Command not found' but 'Permission denied'
> after chmod 000, chmod 777 doesn't work anymore
> Should run minishell instead of printing 'Command not found'

- Add bonus errmsg management:
> `~`       should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar`    should print: `bash: $notavar: ambiguous redirect`

- Fix execution of cwd bin
> ./ls runs /usr/bin/ls and not the copy tin the cwd

- Add 'env' ability to export variables to env.
> `env z=salut`
