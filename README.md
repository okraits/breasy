## breasy - the fast way of browsing

breasy is a simple and fast browser in the tradition of 
[lariza](http://github.com/okraits/lariza).

Written with the Qt5 toolkit, it is based on QWebView (webkit2) right now,
but it will eventually move to QWebEngineView (Chromium).

### Features (currently implemented)

- fast startup and browsing, light on system resources
- provide an URL to load as a commandline argument or enter one in the location bar
- keybindings similar to Firefox
- search the current page
- content zoom

For upcoming features, take a look at the todo list further down this page and stay tuned.

### Why another browser?

Most mainstream browsers (firefox, chrome) are kind of slow and heavy on
system resources. And i don't need all the features of alternative browsers
like dwb, uzbl, qutebrowser etc.

I was quite happy with vain's [lariza](http://github.com/vain/lariza) so i
[forked](http://github.com/okraits/lariza) it to add the features i needed.
But lately webkit(2)gtk seems to have quite some issues so i decided to switch
to Qt and use Qt Webkit for my own browser.

### Requirements

breasy has the following requirements:

- qt5-webkit

### Building and running breasy

Clone this repository:

    git clone https://github.com/okraits/breasy.git

Run *qmake* and *make* afterwards:

    qmake & make

Run the *breasy* binary and optionally provide an URL to open:
    
    ./breasy https://github.com/okraits/breasy

### Usage

#### Keybindings

To focus the location bar to enter an URL:

    CTRL + l

To load the URL just entered in the location bar:

    RETURN

To close the current window:

    CTRL + w

To reload the current page:

    CTRL + r or F5

To enter a word in the location bar to search for in the current page:

    CTRL + f

To increase / decrease the current content zoom level:

    CTRL + '+' / '-'

To go to the previous page in the browsing history:

    ALT + Left

To go to the next page in the browsing history:

    ALT + Right

To stop the current page from loading:

    ESC

### License

This software is released under the terms of the
GNU General Public License v2:

[http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt](http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt)

### Todo list

- tabbed interface
- focus webview after page has loaded
- set tab title after page has loaded
- adblock
- page loadstatus indicator
- keyword based search
- save settings and keybindings in a configuration file
- scripting interface
- validate URLs
- URL autocompletion based on permanent browsing history
- enable plugins
- go back/forward for the search page function
- middle mouse button opens link in new tab
- set useragent string and accepted language
- show URL of the link under the mousepointer in the location bar
