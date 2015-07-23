# aiashow2015
MoS custom firmware (and environment) for the L3D cubes and the AiA show 2015.

This package will allow you to do local development for the L3D cubes
on your Mac. (Linux development is also possible with some rather
simple modifications to these instructions - you won't be able to use
the simulator, though.)

## Setup your environment

The setup is a fairly basic development environment with a couple of
extras which can be installed and managed easily using Homebrew (or
similar).

You will need to:

1. Set up [your machine](docs/machine-setup.md).
2. Everything else in this document.



### Clone the repo and run the setup script.

We are getting so close. Now we just have to copy down the aiashow source code and set it up with the basic firmware installation. This will allow us to build our own versions of the firmware that run our demos.

<pre><code>git clone https://github.com/aiashow2015/aiashow2015.git
cd aiashow2015
cat < conf/bashpash.sh >> $HOME/.profile
</code></pre>

Now, close your Terminal window and open a new one. 

Type <pre><code>cd aiashow2015</code></pre>

This command changes your current working directory to the "aiashow2015" directory. You will need to do this for everything from now on, so I'm going to assume you've done it and stop telling you about it. If you're ever unsure, you can type <code>pwd</code> to find out what directory you are in.

<pre><code>make</code></pre>

Assuming that everything ran without error, you should now see a file called 'mos.bin' in the 'core-bin' directory. (Or 'photon-bin' if you're building for the photon. (Type <code>ls</code> to see the files in your directory. Type <code>ls core-bin</code> to see the files in the core-bin directory.) 

Congratulations! You've just built your first firmware for the cube!

## How to build and deploy cool demos on the cube.

### Finding the unique id of your cube.

_coming soon_

### Building/installing some code.

_coming soon_


## How to use the simulator to develop demos at superspeed!

_coming soon_


## Appendix: Installing Homebrew in your homedir

_coming soon_
