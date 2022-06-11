
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???

##  Execution

- Fix execution multipipe
> `cat | cat | cat` then `<CR><C-C>` the prompt should go to newline.
> `cat | ls` then `<CR><C-C>` the prompt should go to newline.

- Add execution error code management
- Add execution $? feature
- Add ft_exit

- Add SHLVL feature

- Add pipe errmsg management:
> `|`       should print `bash: syntax error near unexpected token \`|'`
> `||`      should print `bash: syntax error near unexpected token \`||'`
> `|||…`    should print `bash: syntax error near unexpected token \`||'`

- Add pipe errmsg management:
> `|`       should print `bash: syntax error near unexpected token \`|'`
> `||`      should print `bash: syntax error near unexpected token \`||'`
> `|||…`    should print `bash: syntax error near unexpected token \`||'`

- Add bonus errmsg management:
> `&`       should print `bash: syntax error near unexpected token \`&'`
> `.`       should print
    bash: .: filename argument required
    .: usage: . filename [arguments]
> `~`       should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar`    should print: `bash: $notavar: ambiguous redirect`

##  Final

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

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

- Fix execution of cwd bin
> ./ls runs /usr/bin/ls and not the copy tin the cwd

- Add 'env' ability to export variables to env.
> `env z=salut`
