# Machine setup

This document will walk you through the steps to set up your machine for L3D
cube development with the aiashow2015 demos. You will need to do these steps
once per machine on which you wish to build the aiashow2015 code.

The steps are:

1. (Optional) Upgrade to Yosemite. (You only need to do this if you want to
run the cube simulator.) 
2. Install XCode.
3. Install Homebrew (Semi-optional. If you have another package manager
installed, you can use that as long as it has all of the packages that we
need. We will assume that you are using Homebrew in the rest of the
documentation.) 
4. Install the dependencies using Homebrew.


## Upgrade to Yosemite

*This step is optional.* You only need to do this step if you want to run the
 L3D simulator. 

To avoid incompatibilities, I suggest you start by upgrading your system to
Mac OS X 10.10 (Yosemite). You can try 10.9 (Mavericks). It might
work. Anything older, and I don't think you'll get the simulator working
without serious hacking. Everything else might work, but you really want the
simulator if you're doing any cube dev.

Before doing this step, make sure that you don't already have Yosemite
installed. (From the Apple menu, choose "About this Mac." If the window says
"OS X Yosemite," then you can skip this step.)

The easiest way to upgrade to Yosemite is using the AppStore.

1. Start the AppStore. (From Finder, hit Cmd-Shift-A. AppStore will be in that
window. Double-click the icon.) 
2. In the Search box, type "Yosemite." You'll see it listed as "OS X
Yosemite." Install/upgrade it by following the instructions. 
3. Go have some coffee. This will take a while.


## Install XCode

1. Once that Yosemite upgrade has completed, go back to the AppStore and
search for XCode.  
2. Install the newest version of XCode that you see in the list. 
3. Go have a snack.

When you come back from your snack, XCode should be installed.

_Be sure to run XCode at least once before moving to the next step._ Agree
to the licensing stuff. When it finally says "Welcome to XCode," you should be
all set.


## Install Homebrew

Homebrew is a Mac OS "package manager." This just means that it will do all of
the annoying parts of installing a whole slew of free software from the
internet. There are several of them. Homebrew is my favorite. (You can use any
one that you want as long as you install all if the right packages.)

Homebrew works best when you install it in the default location,
/usr/local. But sometimes. you might not have write permission there, so you
can install it in your home directory too. If you can, though, put it in the
default place. It's much more efficient, since you can use the pre-built
binaries that Homebrew makes available.

1. Open the Terminal app. (Cmd-Shift-A. Look for Terminal. Double-click.) If
you're going to be doing a lot of this, I recommend keeping Terminal in the
Dock so that you can find it quickly next time.
2. Go to http://brew.sh.
3. At the top of the Homebrew page, there is a single line of code that begins
with 'ruby -e'. Copy that. (This will install into /usr/local. If you need it
somewhere else, check out the next appendix at the bottom of these
instructions.)
4. Then paste it into the Terminal window and hit return.
5. When this is done, type 'brew' and hit return. If it prints out an "Example
usage:" message, you can skip the rest of this. If it says "command not
found," then proceed with the next steps.
6. In the terminal, type (or copy/paste) the following:
<pre><code>export PATH=/usr/local/bin:$PATH'</code></pre>
7. Type 'brew' and hit return. Make sure you get the usage message. Otherwise,
you've done something wrong.


## Install dependencies

In this step, you will use your new Homebrew installation to install all of
the dependencies which you need.

<pre><code>brew tap PX4/homebrew-px4
brew update
brew upgrade
brew install git dfu-util node 
brew install gcc-arm-none-eabi
npm install -g particle-cli
</code></pre>


## Fix your path (#fix-your-path)

_You can only do this step after you have [setup your
repository](repo-setup.md)._ Come back here and do this when you are done with
that step.


cat < conf/bashpash.sh >> $HOME/.profile
