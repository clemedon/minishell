
#           ISSUES

>       help

# //////////////////////// ATHIRION

- Fix redir in redir

- Fix multiple pipe with multiple here_doc

- Fix here_doc when outfile missing

- Fix leak with multiple redir in redir
> < file1 < file2 | b | c | d
> a | b | c < file1 | d < file2

# //////////////////////// CVIDON

- Fix exec signal ctrl-d and status

- Fix heredoc ctrl-c
> Shouldn't display: `minishell: warning: here-document delimited by end-of-line (wanted 'salut')`

# //////////////////////// ???

##  Execution




- Add error code 130 handling
> `data->status = 128 + <numéro_du_signal>`
> C-C, check discord

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
