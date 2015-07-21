lpath_append ()  { lpath_remove $1; export PATH="$PATH:$1"; }
lpath_prepend () { lpath_remove $1; export PATH="$1:$PATH"; }
lpath_remove ()  { export PATH=`echo -n $PATH | awk -v RS=: -v ORS=: '$0 != "'$1'"' | sed 's/:$//'`; }

if [ -d /usr/local/bin ]; then
    lpath_prepend /usr/local/bin
fi

if [ -d /usr/local/share/npm/bin ]; then
    lpath_prepend /usr/local/share/npm/bin
fi

if [ -d $HOME/node_modules/bin ]; then
    lpath_prepend $HOME/node_modules/bin
fi
