
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???

##  Execution

- Protect all open and close
> Create a function to handle file control error

- Fix execution behavior:
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
> `echo ciao > ~`           should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar`    should print: `bash: $notavar: ambiguous redirect`

##  Final

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Remove tokpos
- Remove redlist

- Comply to norm

##  Wtf

- Fix execution cwd executable file
> from cwd: `touch ls; chmod +x ls; ls`
> Shouldn't print: `: Exec format error`

- Add 'env' ability to export variables to env.
> `env z=salut`
