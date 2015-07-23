# Repo setup

The computer code that we are working with is kept in something called a
"repository," or "repo" for short. The repo is just a way to coordinate when
several people are changing the same files at once. See the [Git
tutorial](git-tutorial.md) for more details on how to work with the repo.

In this step, we "clone" the repository on your machine. This gives you access
to all of the files and allows you to change them - confident that you can't
overwrite anyone else's changes.


## Sign up with github.com

We are storing our code on a website called Github. This is a well-known and
respected repository manager that is very popular with the open-source
community. It is also (mostly) free, and that is nice, too.

Before you can interact with the site most effectively, you should go to
<https://github.com/> and sign up with a new username and password. (Please
follow the usual guidelines for secure passwords. Don't use your MoS
password.) Choose the free option - it's all you need!


## Clone the repo (no setup version)

__NOTE:__ At this point, you have two choices. You can follow these
instructions, and everything will work for you, but you will have to type your
name and password every time you interact with the shared version of the
repository. _OR_ you can follow [these instructions](#complex) an never have
to type your username and password again.

If you want to take the quick, but easy, path, follow these instuctions:

<pre><code>git clone https://github.com/aiashow2015/aiashow2015.git
cd aiashow2015
</code></pre>

Now you are in the "working directory" for the aiashow project. Nearly
everything else you do assumes that you have are in this directory, so be sure
to <code>cd</code> back to this directory every time you start work again.

You can find out what directory you are in at any time by typing
<code>pwd</code>. 

Now go [set up git](#git-config).


## Clone the repo (ssh version) (#ssh-setup)

<pre><code>git clone git@github.com:aiashow2015/aiashow2015.git
cd aiashow2015
</code></pre>

Now you are in the "working directory" for the aiashow project. Nearly
everything else you do assumes that you have are in this directory, so be sure
to <code>cd</code> back to this directory every time you start work again.

You can find out what directory you are in at any time by typing
<code>pwd</code>.

Now go [set up git](#git-config).


## Set up your git configuration (#git-config)

Whew. We're almost done. Just a couple more details:

Go and do these last two steps:

1. [Set up your name in
git.](https://help.github.com/articles/setting-your-username-in-git/)
2. [Set up your email in
git.](https://help.github.com/articles/setting-your-email-in-git/) Follow the
instructions "for every repository on your computer," unless you know that you
shouldn't. (But in that case, you probably don't need these walkthroughs.)

Now that we have a repo, we can do the [final little piece of machine setup](machine-setup.md#fix-your-path). Go
do it now.


## Set up your ssh keys (#complex)

This is definitely the way to go. You have to follow these instructions once
per machine, but your life will be greatly improved in the future. They're
really not hard, but they do require some attention to detail.

Github has written better instructions for this than I could ever hope to. Go
[here](https://help.github.com/articles/generating-ssh-keys/#platform-mac) and
do what they tell you.

After you have finished this step, go to the [alternative instructions for
cloning your repo](#ssh-setup).

