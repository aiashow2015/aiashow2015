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


### Install XCode

1. Once that Yosemite upgrade has completed, go back to the AppStore and
search for XCode.  
2. Install the newest version of XCode that you see in the list. 
3. Go have a snack.

When you come back from your snack, XCode should be installed.

_Be sure to run XCode at least once before moving to the next step._ Agree to
the licencing stuff. When it finally says "Welcome to XCode," you should be
all set.

