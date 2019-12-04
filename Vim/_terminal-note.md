# Terminal
ls -a -l -h -G -S
ls -alhGS
all, long, color, sort

cd cd ~ home dir
cd / root of drive
cd - previous dir

https://github.com/0nn0/terminal-mac-cheatsheet


tree -L  1 -C -A -h -d
level 1, color, ANSI, human readable size, directory only

cmus
cmatrix
ffmpeg
youtube-dl
wget
htop
nmap
imagemagisk


# Python
pyenv versions
pyenv shell

pip list
pip search
pip show
pip install/uninstall
victor$ ls -l `which pip`
-rwxr-xr-x  1 wei_li  staff  416  5 Nov 23:08 /Users/wei_li/.pyenv/shims/pip
victor$ ls -l `which pip3`
-rwxr-xr-x  1 wei_li  staff  416  5 Nov 23:08 /Users/wei_li/.pyenv/shims/pip3

# pip search error
Upgrade pip as follows: ```_curl https://bootstrap.pypa.io/get-pip.py | python_``` Note: You may need to use sudo python above if not in a virtual environment.
(Note that upgrading pip using pip i.e pip install --upgrade pip will also not upgrade it correctly. It's just a chicken-and-egg issue. pip won't work unless using TLS >= 1.2.)
As mentioned in [this detailed answer](https://stackoverflow.com/questions/49748063/pip-install-fails-for-every-package-could-not-find-a-version-that-satisfies/49748494#49748494), this is due to the recent TLS deprecation for pip. Python.org sites have stopped support for TLS versions 1.0 and 1.1.

# PIL
You can try using Pillow instead, which is a PIL fork:
_pip install Pillow_
To import use following:
_from PIL import Image_


