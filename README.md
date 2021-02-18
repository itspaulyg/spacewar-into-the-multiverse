# Spacewar! Into the Multiverse

## Proposal 
We propose to recreate the classic game Spacewar! which was developed in the 1960’s by the hackers at MIT. The game consists of two spacecrafts attempting to kill one another with a set amount of torpedoes. We plan to limit the number of torpedoes each spacecraft has and have the spacecrafts continue to move even after you let go of the movement keys (to create a ‘gliding in space’ movement). We plan to have a starry night background and a sun in the center which will destroy your spacecraft if you come in contact with it, similar to the hackers’ implementation. We will also have the hyperspace function, which upon activation will remove the player’s spacecraft from the field until reactivation (about 2 or 3 seconds), whereupon the spacecraft will reappear at a random location on the field.

## Building
We are using SDL as our graphics library for this project. To have all features available use this command: 

sudo apt-get install build-essential git make cmake autoconf automake libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libdbus-1-dev libudev-dev libgles2-mesa-dev libegl1-mesa-dev libibus-1.0-dev fcitx-libs-dev libsamplerate0-dev libsndio-dev libwayland-dev libxkbcommon-dev

A Makefile is provided so that you just have to type in the command 'make' and it will start running the program. Please run 'make clean' prior to pushing any changes to GitHub.
