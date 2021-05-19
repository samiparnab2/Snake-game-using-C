# Snake-game-using-C
This is the snake game written in C for DOS using BGI library.


## Dependencies
* DOSBOX Emulator
* TURBO-C++ 

## Visual Demo

![](https://media.giphy.com/media/LP0RU3fpLSEXpW6SOl/giphy.gif)

## How to Run


* First of all you need to  download TURBO-C++ setup from [here](https://www.javatpoint.com/cpp/software/tc3.zip)

* __Steps For Linux__

    1. For debian based systems (Ubuntu,Linux Mint etc.) can install __dosbox__ with this command -
        ```bash
        sudo apt-get install dosbox
        ```
        For other Linux flavors like RHEL, CentOS, and Fedora, you can compile and install it from the source as follows.

        1. Download __dosbox__ from [here](https://www.dosbox.com/download.php?main=1)
        1. Extract the tar.gz file of DOSBOX Setup.
        1. Go to the extracted folder.
        1. Run these commands as __sudo__ -
            ```bash
            ./configure
            make
            make install
            ```
         Now you can run DOSBOX by typing __dosbox__ in terminal.

    1. Now extract __tc3.zip__ file to your __home (~/)__ directory.
    1. Open terminal and run __dosbox__.
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
    1. Now __TURBO-C++__ is installed.
    1. To open __TURBO-C++__ automatically within dosbox go to __~/.dosbox__ , open the __.conf__ file and add these lines to the end of the file -
        ```dos
        mount c: ~
        c:
        cd TC/BIN
        TC
        ```
        Now __TURBO-C++__ will automatically start when you open dosbox.
* __Steps for Windows__

    1. Download __dosbox__ from [here](https://www.dosbox.com/download.php?main=1).
    1. Open the setup and Install (add shortcut to desktop for easy access).
    1. Now go to __C:__ Drive and create a folder named __TC__ .
    1. Extract __tc3.zip__ file to  __C:\TC\\__ directory.
    1. Run __dosbox__.
    1. In __dosbox__ type these commands -
        ```dos
        mount c: C:\TC\
        c:
        cd tc3
        install
        ```
    1. The __TURBO-C++__ setup will open then hit __ENTER__.
    1. Change the __SOURCE DRIVE__ TO __C__ and hit __ENTER__.
    1. Check if __SOURCE PATH__ should be __\tc3__ and hit 
    __ENTER__.
    1. Goto __Start Installation__ , hit ENTER and wait for the Installation process to be finished.
    1. Now __TURBO-C++__ is installed. To open __TURBO-C++__ automatically within dosbox go to __~/.dosbox__ , open the __.conf__ file and add these lines to the end of the file -
        ```dos
        mount c: ~
        c:
        cd TC/BIN
        TC
        ```
        Now __TURBO-C++__ will automatically start when you open dosbox.
* Now download this repository and move __GAME(NO_REFRESH).C__ and __GAME(REFRESH).C__ files to  __~/TC/BIN__ _(for Linux)_  or   __C:\TC\TC\BIN__ _(for Windows)_.
* Run dosbox.
* __Turbo-c++__ should be opened automatically. Goto __File>Open__ and open any of these __GAME(NO_REFRESH).C__ and __GAME(REFRESH).C__ files.
* Go to __Option>Linker>Libraries__ and make sure that __Graphics Library__ is checked.
* Press __Alt+R__ and run the game.
