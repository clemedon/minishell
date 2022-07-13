
#           ISSUES

>       help

# //////////////////////// ATHIRION

# //////////////////////// CVIDON

# //////////////////////// ???

echo    \n hola
""''echo hola""'''' que""'' tal""''
echo \$HOME
echo $UID
echo $USER$var\$USER$USER\$USERtest$USER
echo $""
echo $"HOME"
echo $''HOME
echo $""HOME
echo $"HO""ME"
echo $'HO''ME'
echo $'HOME'

export ""
export HO$?LA=bonjour ; env
export HOLA=$HOME

export HOLA="bonjour         "
export HOLA="  -n bonjour   "

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 0 <<<<<<<<<<<<<<<<<<<<

DONE


>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 280 <<<<<<<<<<<<<<<<<<<<


>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 523 <<<<<<<<<<<<<<<<<<<<

DONE


>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 619 <<<<<<<<<<<<<<<<<<<<


- Fix status code
> `<C-C>` then `|` then `echo $?`

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
