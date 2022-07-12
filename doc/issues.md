
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???

- Fix parse command
>

- Fix expand numeric var
> `echo "$100"` should print `00`

- Fix expand var =
> `echo "$USER="` should print `cvidon=`

- Fix leak redir
> 2 files 1 redir
> leak & redir pas

- Fix parse command
> "" "" "" break minishell.

- Fix parsing
> echo "d"d should print dd not d d.

- Fix exit code offset
> exi; exit; echo $? Should not return 127.

##  Wtf

- Prompt on hold
> `$""$`

- Backslash is a character
> `rm \\  <-`

- Maybe remove tokpos

- Fix errmsg
> `/`, `//`, `///` etc. Should print `Is a directory` not `Permission denied`

- Exec signals
> `cat | ls` + SIGINT/SIGQUIT not handled.
> Should be same as `cat` + SIGINT/SIGQUIT.

- Fix << STOP cat << HELL cat >
> should display 'cat: cat: No such file or directory'
> error code should be 1 and not 0

Mysterious leak
> `<, )`

- Fix SIGQUIT and SIGINT prompt
> `$ cat<CR>salut<C-\>` shouldn't print `salut` in the prompt.
> `$ cat<CR>salut<C-C>` shouldn't print `salut` in the prompt.
> Or `$ yes<CR>salut<C-C>` shouldn't print `salut` in the prompt.

- Fix execution cwd executable file
> from cwd: `touch ls; chmod +x ls; ls`
> Shouldn't print: `: Exec format error`

- Fix execution of minishell in minishell after chmod
> `chmod 000 minishell`
> Shouldn't print : `Command not found` but `Permission denied`
> after `chmod 000`, `chmod 777` doesn't work anymore
> Should run minishell instead of printing `Command not found`

- Add bonus errmsg management:
> `~` should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar`    should print: `bash: $notavar: ambiguous redirect`

- Fix execution of cwd bin
> `./ls` should runs `/usr/bin/ls` instead an eventual cwd located `ls`
