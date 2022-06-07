

#           ISSUES

>       help

# //////////////////////// ATHIRION

##  Parsing

- Fix quote expansion export
> 'export salut="au revoir" should expand 'salut=au revoir' and not
> just 'salut='
> `export var1="|" var2="ls"` should work fine.

# //////////////////////// CVIDON

- Add ft_exit

##  Exec

# //////////////////////// ???

##  Execution

- Add errmsg management:
> `" "`     missing a `<space>` at `:command not found` errmsg first char.
> `""`      and `''` should output `""` / `'': command not found` instead nothing.
> `|`       should print `bash: syntax error near unexpected token \`|'`
> `||`      should print `bash: syntax error near unexpected token \`||'`
> `|||…`    should print `bash: syntax error near unexpected token \`||'`
> `&`       should print `bash: syntax error near unexpected token \`&'`
> `.`       should print
    bash: .: filename argument required
    .: usage: . filename [arguments]
> `~`       should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > ~`           should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar`    should print: `bash: $notavar: ambiguous redirect`
> `$notavar`                should not print `: command not found`

- Add execution error code management

- Add execution $? feature

- Add execution '`./<program>`' feature

- Fix exec when cwd files named as programs are called
> 'ls: command not found' if there is a 'ls' file in the CWD.
> Might be fixed with the handling of *'./<program>' feature*. Or the
> environ check for path before the exec a command.

- Add SHLVL feature

- Fix execution errors:
> `cat | cat | cat` then `<C-C>` shouldn't quit minishell.
> `cat | ls` then `<C-C>` shouldn't duplicate the prompt + should print `ls`.

##  Expansion

##  Quotes parsing

- Fix export builtin (linked to *quote timing*?)
> `export var="'cat Makefile'" OR export var='"cat Makefile"'`
> `export var="<anything><space>"`
> shouldn't print errors.

##  Final

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Remove tokpos

- Comply to norm
