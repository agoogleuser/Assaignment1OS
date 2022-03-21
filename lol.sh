#!/bin/sh

clear
echo "Compiling program using GCC"
echo "_______________________________"
gcc -o .exec main.c
exitco=$?

printf '\nCompiling exit code = 0x%0.8X = %d\n' $exitco $exitco

if [ $exitco -eq 0 ]
then
	echo "Executable is saved as .exec"
	echo "=================================="
	echo "Executing The Program"
	echo "__________________________________"
	echo " "
	./.exec
	printf 'Execution Complete. Program Exited with code 0x%0.8X = %d\n' $? $?
fi
