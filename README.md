# DOMINUS

TO DO

## Src

This folder contains an example for autotools use in the folder domoticz.
In order to compile it, run:

- $ ./autogen.sh
- $ ./configure
- $ make


## Dockerfile

This file allows you to create an image based on a debian image, and that automatically download and compile the buildroot for the RPi3.

This image includes :
* A root session which password is `toor`
* A user session which name is `user_1` and password `user_1pw`
* Domoticz is installed and automatically starts when the RPi3 boots.

In order to creates this docker, you just have to run this command line where the .dockerfile is :

		docker build .

You can give the image a name with the `-t` option.

NB : The whole running of this command took me about 40 minutes. It works (and have been tested) with a stable internet connexion (there are not the settings for the ENSTA's proxy, and it doesn't work with the unstable wifi connexion of the school).


The ID of the image is returned at the end of the running of the build command. Otherwise, you can find it by running this command :

		docker image ls

After that, you can create a docker container from the image by running :

		docker run -it <image_ID> 

The image for the sdcard can be found in `/root/buildroot-2017.08/outputs/image`. 
You can also copy it by running :

		docker cp <docker_ID>:/root/buildroot-2017.08/output/images/sdcard.img .

