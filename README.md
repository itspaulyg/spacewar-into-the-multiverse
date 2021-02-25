# Spacewar! Into the Multiverse

## Proposal 
We propose to recreate the classic game Spacewar! which was developed in the 1960’s by the hackers at MIT. The game consists of two spacecrafts attempting to kill one another with a set amount of torpedoes. We plan to limit the number of torpedoes each spacecraft has and have the spacecrafts continue to move even after you let go of the movement keys (to create a ‘gliding in space’ movement). We plan to have a starry night background and a sun in the center which will destroy your spacecraft if you come in contact with it, similar to the hackers’ implementation. We will also have the hyperspace function, which upon activation will remove the player’s spacecraft from the field until reactivation (about 2 or 3 seconds), whereupon the spacecraft will reappear at a random location on the field.

## Post-MVP-Development Reflection
Spacewar! was the result of multiple insanely passionate students at MIT spending days and nights in front of the PDP-1 computer. The original hackers: Steve Russell, Bob Saunders, Peter Samson, and many others loved to work on the game by adding additional features. In a way, one can view Spacewar! as one of the first open-source projects of all time—anyone who had access to the code could contribute to or vary the software any way they wanted.
This videogame, in hindsight, was an embodiment of the Hacker Ethics and culture at MIT—it was freely available to others, it was an innovative way to use the computer, and it was considered a beautiful creation. Communities of people grew around the game as more people participated in playing the game and also developing the game.

This ancestor of videogames played a huge role in helping many people realize the true, limitless potential of the computer; it announced to the world that a computer was more than just a machine that would solve equations. In building a recreation of Spacewar! we could not help but wonder in awe at how the originals hackers created such an entertaining and complex game on the PDP-1 with punch tapes. Even building it on the much higher language of C++ and using the SDL2 graphics library, we found it quite challenging to build something like Spacewar!. There is so much math and logic involved in this small, seemingly simple game that many people would easily look over. This is one of the original “hacks” that really deserve the status of being a “hack”.


## Building
We are using SDL as our graphics library for this project. To have all features available use this command: 

sudo apt-get install build-essential git make cmake autoconf automake libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libdbus-1-dev libudev-dev libgles2-mesa-dev libegl1-mesa-dev libibus-1.0-dev fcitx-libs-dev libsamplerate0-dev libsndio-dev libwayland-dev libxkbcommon-dev

A Makefile is provided so that you just have to type in the command 'make' and it will start running the program. Please run 'make clean' prior to pushing any changes to GitHub.

## Building (Linux)
`sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev`