# qres
Win32 Window Mover

```
Usage: c:\Program Files\qres\qres.exe [options]
qres

Options:
  -?, -h, --help                           Displays this help.
  -v, --version                            Displays version information.
  -x, --x-position <pos>                   x position of window
  -y, --y-position <pos>                   y position of window
  -w, --width <width>                      width of window
  -t, --height <height>                    height of window
  -f, --window-title <regexp>              regexp to find window-title(s)
  -b, --borderless <borderless>            borderless
  -a, --blankborders <blankborders>        blankborders
  -g, --gamekeepalive <gamekeepalive>      gamekeepalive
  -i, --waitforwindow <waitforwindow>      seconds to wait for the window
                                           (title)
  -d, --delaymovewindow <delaymovewindow>  seconds to delay window move

```

# examples

```
qres.exe -f ^Thunderbird$ -x 3962 -y 510 -w 1160 -t 920


qres.exe -f "^vmwareplayervm" -x 2700 -y 247 -w 2000 -t 1200 -b false -i 60 -d 10

qres.exe -g true -f "World of Warcr"
```
