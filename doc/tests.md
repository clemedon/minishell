#   TESTS

- fixed
* tofix

##  Commandline

- echo ""
- echo "$NOP"
- echo "something"
- echo "$USER"
- echo " " $USER
- echo $123A
- echo $UU $USER
- $U$USER

* < Makefile > out | echo salut > out
* < Makefile cat > out | echo salut > out
* < Makefile cat > out | wc -l > out
* < Makefile cat > out | wc -l >> out
* << STOP cat > out | wc -l >> out
* < Makefile wc -l > out | < Makefile grep CC >> out

##  Behavior

* Try:
    minishell$ yes<CR>
    minishell$ salut<CR>
    minishell$ <C-C>
> Signals ?
