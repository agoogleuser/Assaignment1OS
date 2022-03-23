# Lab 1 Assaignment

---
Team Members:
<div dir="rtl">

ارميا خيري فهمي سوس 18010293

حسن مصطفى حسن علي 18010573

احمد فخر
</div>

___
## Pre-Acqusisions
* Access to a linux terminal which can be either via 
    1. Dual booting or already having to a linux-based OS.
    2. Running a Virtual Machine for Linux
    3. Using WSL [Windows Subsystem for Linux] on your Windows 10/11 machine.
* Code editor. (VScode is **VERY RECOMMENDED**)
* `git` installed on your Linux Operating System. 

### Extensions Required for VScode
1. Microsoft C/C++ Extension Pack.
2. github Extension.
3. GitLens Extension. (optional)
4. Liveshare Extension Pack.
    * this extension is recommended if we needed to write some code together.
## Assignment Overview:
This Tasks aima to mimic how a terminal or a commandline works, and practicing multi-process programs. In this task we learned about `fork()`
, `wait()` to make a new process and how to handle it.

### Getting the files.
You can simply download the files from Here, but I recommend using `git` instead for the sake of our sanity.

Watch this [playlist](https://www.youtube.com/watch?v=ACOiGZoqC8w&list=PLDoPjvoNmBAw4eOj58MZPakHjaO3frVMF) (at least the first two:four videos) in order to fully understand `git` meaning. and I recommend using [VScode for github](https://www.youtube.com/watch?v=3Tn58KQvWtU "How to use git on VScode")  because they make these things easier.
### Running the script using the terminal
I ***Really*** don't like `CODE::BLOCKS` especially on linux since it tends to be very buggy on Ubuntu 99% of the time, at least that was my experience, So I recommend using the terminal. but I made it easier to use it for compiling and running the project files.

There are two scripts I worte: `lol.sh` is used to comple and run the program -the `main.c` file only-, if no errors were found.
and `lol_cpp.sh` which is used to do the same as `lol.sh` but for `main.cpp` file.

In order to run one of the script, first you have to navigate to the folder where the files exists by using `cd` command. For example: if you run the terminal directly, the default directory it will be at is `/home/<your username>`. to change it you simply need to navigate to the folder that has the code, Assuning this folder is located in `/home/name/github/Assaignment1OS`, you wull write the following
```bash
cd /home/name/github/Assaignment1OS
```
It will navigate to that folder. Now you can proceed the next steps.

Make sure the script is executable, or just make it executable. This is only done once
```bash
chmod +x lol.cpp
chmod +x lol_cpp.sh
```

In order to run the script, you will write the following line to compile and run the c file
```bash
./lol.sh
```
or the following line for the cpp file.
```bash
./lol_cpp.sh
```

## *Work in progress...*
Description of the Probect and how to use it will be left here.