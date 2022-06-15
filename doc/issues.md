
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???

##  Execution

- Fix multiple pipe with multiple here_doc

- Fix here_doc when outfile missing

- Fix env
> 'env salut' should display 'env: 'salut': No such file or directory'
> and  not the env
> the error code should be 127

- Fix leak
> < file1 < file2 | b | c | d 
> a | b | c < file1 | d < file2

- Add execution $? feature
- Add ft_exit

- Fix execution multipipe
> `cat | cat | cat` then `<CR><C-C>` the prompt should go to newline.
> `cat | ls` then `<CR><C-C>` the prompt should go to newline.

- Add error code 130 handling
> C-C, check discord

- Fix error code 13
> `touch file; chmod 000 file; echo hello > file` should return 1.

- Add SHLVL feature


##  Final

- Protect every dup2

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Close all fds that remains open

- Check every output STD
> Check that they're displayed the right STD.OUT/ERROR

- Remove tokpos
- Remove redlist

- Comply to norm

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
