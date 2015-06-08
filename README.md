# aiashow2015
MoS custom firmware (and environment) for the L3D cubes and the AiA show 2015.

This package will allow you to do local development for the L3D cubes on your Mac. (Linux development is also possible with some rather simple modifications to these instructions - you won't be able to use the simulator, though.) 

## Setup your environment

The setup is a fairly basic development environment with a couple of extras which can be installed and managed easily using Homebrew (or similar).

### Upgrade to Yosemite

To avoid incompatibilities, I suggest you start by upgrading your system to Mac OS X 10.10 (Yosemite). You can try 10.9 (Mavericks). It might work. Anything older, and I don't think you'll get the simulator working without serious hacking. Everything else might work, but you really want the simulator if you're doing any cube dev. 

Before doing this step, make sure that you don't already have Yosemite installed. (From the Apple menu, choose "About this Mac." If the window says "OS X Yosemite," then you can skip this step.

The easiest way to upgrade to Yosemite is using the AppStore.

> 1. Start the AppStore. (From Finder, hit Cmd-Shift-A. AppStore will be in that window. Double-click the icon.)
> 2. In the Search box, type "Yosemite." You'll see it listed as "OS X Yosemite." Install/upgrade it by following the instructions.
> 3. Go have some coffee. This will take a while.

### Install XCode

> 1. Once that Yosemite upgrade has completed, go back to the AppStore and search for XCode. 
> 2. Install the newest version of XCode that you see in the list. 
> 3. Go have a snack.

### Install Homebrew

Homebrew is a Mac OS "package manager." This just means that it will do all of the annoying parts of installing a whole slew of free software from the internet. There are several of them. Homebrew is my favorite. (You can use any one that you want as long as you install all if the right packages.)

Homebrew works best when you install it in the default location, /usr/local. But sometimes. you might not have write permission there, so you can install it in your home directory too. If you can, though, put it in the default place. It's much more efficient, since you can use the pre-built binaries that Homebrew makes available. 

> 2. Open the Terminal app. (Cmd-Shift-A. Look for Terminal. Double-click.) If you're going to be doing a lot of this, I recommend keeping Terminal in the Dock so that you can find it quickly next time.
> 1. Go to http://brew.sh.
> 3. At the top of the Homebrew page, there is a single line of code that begins with 'ruby -e'. Copy that. (This will install into /usr/local. If you need it somewhere else, check out the next appendix at the bottom of these instructions.)
> 4. Then paste it into the Terminal window and hit return. 
> 5. When this is done, type 'brew' and hit return. If it prints out an "Example usage:" message, you can skip the rest of this. If it says "command not found," then proceed with the next steps. 
> 6. In the terminal, type (or copy/paste) the following:
> <pre><code>echo 'export PATH=/usr/local/bin:$PATH' >> ~/.bash_profile</code></pre>
> 7. Now, close that Terminal window, and open a new one. 
> 8. Type 'brew' and hit return. Make sure you get the usage message. Otherwise, you've done something wrong.

### Now, install the dependencies using homebrew. 

> 1. This is easy.
> <pre><code>brew install git</code></pre>
