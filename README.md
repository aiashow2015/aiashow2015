# aiashow2015
MoS custom firmware (and environment) for the L3D cubes and the AiA show 2015.

This package will allow you to do local development for the L3D cubes on your Mac. (Linux development is also possible with some rather simple modifications to these instructions - you won't be able to use the simulator, though.) 

## Setup your environment

The setup is a fairly basic development environment with a couple of extras which can be installed and managed easily using Homebrew (or similar).

### Upgrade to Yosemite

To avoid incompatibilities, I suggest you start by upgrading your system to Mac OS X 10.10 (Yosemite). You can try 10.9 (Mavericks). It might work. Anything older, and I don't think you'll get the simulator working without serious hacking. Everything else might work, but you really want the simulator if you're doing any cube dev. 

Before doing this step, make sure that you don't already have Yosemite installed. (From the Apple menu, choose "About this Mac." If the window says "OS X Yosemite," then you can skip this step.

The easiest way to upgrade to Yosemite is using the AppStore.

1. Start the AppStore. (From Finder, hit Cmd-Shift-A. AppStore will be in that window. Double-click the icon.)
2. In the Search box, type "Yosemite." You'll see it listed as "OS X Yosemite." Install/upgrade it by following the instructions.
3. Go have some coffee. This will take a while.

### Install XCode

1. Once that Yosemite upgrade has completed, go back to the AppStore and search for XCode. 
2. Install the newest version of XCode that you see in the list. 
3. Go have a snack.

When you come back from your snack, XCode should be installed. You should be sure to run XCode at least once before moving to the next step. Agree to the licencing stuff. When it finally says "Welcome to XCode," you should be all set.

### Install Homebrew

Homebrew is a Mac OS "package manager." This just means that it will do all of the annoying parts of installing a whole slew of free software from the internet. There are several of them. Homebrew is my favorite. (You can use any one that you want as long as you install all if the right packages.)

Homebrew works best when you install it in the default location, /usr/local. But sometimes. you might not have write permission there, so you can install it in your home directory too. If you can, though, put it in the default place. It's much more efficient, since you can use the pre-built binaries that Homebrew makes available. 

2. Open the Terminal app. (Cmd-Shift-A. Look for Terminal. Double-click.) If you're going to be doing a lot of this, I recommend keeping Terminal in the Dock so that you can find it quickly next time.
1. Go to http://brew.sh.
3. At the top of the Homebrew page, there is a single line of code that begins with 'ruby -e'. Copy that. (This will install into /usr/local. If you need it somewhere else, check out the next appendix at the bottom of these instructions.)
4. Then paste it into the Terminal window and hit return. 
5. When this is done, type 'brew' and hit return. If it prints out an "Example usage:" message, you can skip the rest of this. If it says "command not found," then proceed with the next steps. 
6. In the terminal, type (or copy/paste) the following:
<pre><code>export PATH=/usr/local/bin:$PATH'</code></pre>
7. Type 'brew' and hit return. Make sure you get the usage message. Otherwise, you've done something wrong.

### Now, install the dependencies using homebrew

In this step, you will use your new Homebrew installation to install all of the dependencies which you need.

<pre><code>brew tap PX4/homebrew-px4
brew update
brew upgrade
brew install git dfu-util node 
brew install gcc-arm-none-eabi
npm install -g particle-cli
</code></pre>


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
