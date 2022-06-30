
#           ISSUES

>       help

# //////////////////////// ATHIRION

- Fix redir
> echo salut > out > toto

# //////////////////////// CVIDON

- Protect all the signal
> if (signal(blabla) == SIG_ERR) print(errno);

- Protect every dup2

- Close all fds that remains open

- Check every output STD
> Check that they're displayed the right STD.OUT/ERROR

# //////////////////////// ???

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
