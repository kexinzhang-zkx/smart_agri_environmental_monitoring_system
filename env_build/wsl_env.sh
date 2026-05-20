wsl --set-default-version 1
wsl --install Ubuntu-22.04
sudo apt-get update
sudo apt-get install gcc make libsdl2-dev
sudo ln -s /usr/lib/x86_64-linux-gnu/libmpfr.so.6 /usr/lib/x86_64-linux-gnu/libmpfr.so.4
