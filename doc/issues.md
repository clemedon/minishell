
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???


- Fix heredoc signals
> `SIG_INT` then `<< STOP cat |` then `echo $?` shouldnt return 130.

- Check substr
> Check substr (strlen **-1**)

- Normify
> Norm

##  Wtf

- Backslash is a character
> `rm \\  <-`

- Maybe remove tokpos

- Fix errmsg
> `/`, `//`, `///` etc. Should print `Is a directory` not `Permission denied`

- Exec signals
> `cat | cat` + SIGINT/SIGQUIT not handled.
> Should be same as `cat` + SIGINT/SIGQUIT.

- Fix << STOP cat << HELL cat >
> should display 'cat: cat: No such file or directory'
> error code should be 1 and not 0

- Add bonus errmsg management:
> `~` should print `bash: /mnt/nfs/homes/cvidon: Is a directory`
> `echo ciao > $notavar` should print: `bash: $notavar: ambiguous redirect`
