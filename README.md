## breasy - the fast way of browsing

breasy is a simple and fast browser in the tradition of 
[lariza](http://github.com/okraits/lariza).

Written with the Qt5 toolkit, it is based on QWebView (webkit2) right now,
but it will eventually move to QWebEngineView (Chromium).

### Features (currently implemented)

- fast startup and browsing, light on system resources
- slim userinterface with tabs
- opens a given number of URLs provided as commandline arguments on startup
- default keybindings similar to Firefox
- search the current page
- keyword based search: enter "wi linux" to search wikipedia for "linux"
- content zoom
- browser plugins are enabled
- simple text configuration file

For upcoming features, take a look at the 
[todo list](#todo-list-in-descending-but-not-absolute-order) and stay tuned.

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

Run the *breasy* binary and optionally provide some URLs to open:
    
    ./breasy https://github.com/okraits/breasy http://archlinux.org

### Usage

#### Configuration

To modify the default settings, edit the file *$HOME/.config/breasy/breasy.conf*.
It is created on startup if it doesn't exist.

For keyword based searching, add a section *keywordsearch*:

	[keywordsearch]
	go="https://www.google.de/?gws_rd=ssl#q=%s"
	wi="https://de.wikipedia.org/w/index.php?title=Special:Search&search=%s"

#### Keybindings

To focus the location bar to enter an URL:

    CTRL + l

To load the URL just entered in the location bar:

    RETURN

To create a new tab:

    CTRL + t

To go to the next tab:

    CTRL + Page Down

To go to the previous tab:

    CTRL + Page Up

To close the current tab (or window, if you are on the last remaining tab):

    CTRL + w

To open a link in a new tab:

	Middle Mousebutton or CTRL + Left Mousebutton

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

To load the startpage defined in the configuration file:

	ALT + Home

To stop the current page from loading:

    ESC

### License

This software is released under the terms of the
GNU General Public License v2:

[http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt](http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt)

### Todo list (in descending, but not absolute order)

- detect a running breasy instance and open a new tab
- share websession across several webviews
- adblock
- content zoom must affect all existing webviews
- scripting interface
- open local files
- save keybindings in configuration file
- set useragent string and accepted language
- URL autocompletion based on permanent browsing history
- show URL of the link under the mousepointer in the location bar
- mark https connections in the location bar (textcolor green)
- show favicon in location bar
- show load progress as a filling background of the location bar
