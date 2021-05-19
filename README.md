# Snake-game-using-C
This is the snake game written in C for DOS using BGI library.


## Dependencies
* DOSBOX Emulator
* TURBO-C++ 

## How to Run


* First of all you need to  download TURBO-C++ setup from [here](https://www.javatpoint.com/cpp/software/tc3.zip)

* __Steps For Linux__

    1. For debian based systems (Ubuntu,Linux Mint etc.) can install __dosbox__ with this command -
        ```bash
        sudo apt-get install dosbox
        ```
        For other Linux flavors like RHEL, CentOS, and Fedora, you can compile and install it from the source as follows.

        1. download __dosbox__ from [here](https://www.dosbox.com/download.php?main=1)
        1. Extract the tar.gz file of DOSBOX Setup.
        1. Go to the extracted folder.
        1. Run these commands as __sudo__ -
            ```bash
            ./configure
            make
            make install
            ```
    1. Now you can run DOSBOX by typing __dosbox__ in terminal.

    1. Now extract tc3.zip folder to your __home (/~)__ directory.
    1. open terminal and run __dosbox__.
    1. In __dosbox__ type these commands -
        ```dos
            mount c: ~
            c:
            cd tc3
            install
        ```
    1. The __TURBO-C++__ setup will open then hit __ENTER__.
    1. Change the __SOURCE DRIVE__ TO __C__ and hit __ENTER__.
    1. Check if __SOURCE PATH__ should be __\tc3__ and hit 
    __ENTER__.
    1. Goto __Start Installation__ , hit ENTER and wait for the Installation process to be finished.
    1. Now __TURBO-C++__ is installed  

