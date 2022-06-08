
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???

##  Execution

- Add pipe errmsg management:
> `|`       should print `bash: syntax error near unexpected token \`|'`
> `||`      should print `bash: syntax error near unexpected token \`||'`
> `|||…`    should print `bash: syntax error near unexpected token \`||'`

- Add execution '`./<program>`' feature

- Fix execution cwdfile named as prgs
> When a file in CWD has the name of a program.
> 'ls: command not found' if there is a 'ls' file in the CWD.
> Might be fixed with the handling of *'./<program>' feature*. Or the
> environ check for path before the exec a command.

- Fix execution behavior:
> `cat | cat | cat` then `<CR><C-C>` the prompt should go to newline.
> `cat | ls` then `<CR><C-C>` the prompt should go to newline.

- Add execution error code management
- Add execution $? feature

- Add SHLVL feature

- Add ft_exit

- Add bonus errmsg management:
> `&`       should print `bash: syntax error near unexpected token \`&'`
> `.`       should print
    bash: .: filename argument required
    .: usage: . filename [arguments]
> `~`       should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > ~`           should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar`    should print: `bash: $notavar: ambiguous redirect`

##  Final

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Remove tokpos
- Remove redlist

- Comply to norm

##  Wtf

- Add 'env' ability to export variables to env.
> `env z=salut`
