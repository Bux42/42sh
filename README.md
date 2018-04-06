# 42sh

## Introduction

42sh is a basic shell

It is not done yet, don't judge

![42sh gif](https://i.imgur.com/cMiHJQN.gif)

## How to use

git clone https://github.com/Bux42/42sh.git

cd 42sh

make

./21sh

## Show debug

This shell prints it's debug in another terminal

Open a new terminal, type the command tty

Then launch the shell with the tty path as argument

Example: ./21sh /dev/ttys001


## Features

Keys|Functions|
:-:|:--
<kbd>Opt</kbd>+<kbd>K</kbd><br><kbd>Opt</kbd>+<kbd>W</kbd><br><kbd>Opt</kbd>+<kbd>P</kbd>|Copy From Cursor to end<br>From Cursor to beginning<br>Paste
<kbd>Opt</kbd>+<kbd><</kbd><br><kbd>Opt</kbd>+<kbd>></kbd>|Move per words.
<kbd>Opt</kbd>+<kbd>^</kbd><br><kbd>Opt</kbd>+<kbd>v</kbd>|Move per line.
<kbd>Ctrl</kbd>+<kbd>L</kbd>|Clear screen.
<kbd>Ctrl</kbd>+<kbd>R</kbd>|Search History Backward.
<kbd>Ctrl</kbd>+<kbd>F</kbd>|Search History Forward.
