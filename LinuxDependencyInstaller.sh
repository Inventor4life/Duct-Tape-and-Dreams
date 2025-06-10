#!/bin/bash

# SFML Dependencies
sudo apt update && sudo apt install \
     libxrandr-dev \
     libxcursor-dev \
     libxi-dev \
     libudev-dev \
     libflac-dev \
     libvorbis-dev \
     libgl1-mesa-dev \
     libegl1-mesa-dev \
     libdrm-dev \
     libgbm-dev \
	 libfreetype6-dev # SFML relies on FreeType, which isn't installed by the script on their website: https://www.sfml-dev.org/tutorials/3.0/getting-started/cmake/
