# Nibbler

The C++ classic snake game made with dynamic class loading

## Usage
### Installation
	$ git clone https://github.com/ROGERNDABA/Nibbler.git
	$ cd Nibbler
	$ . ./install
### Usage
	$ ./nibbler <width> <height> <libname>

|     KEYS    	|      USAGE      	|
|:-----------:	|:---------------:	|
|   ARROW_UP  	|     MOVE_UP     	|
|  ARROW_DOWN 	|    MOVE_DOWN    	|
|  ARROW_LEFT 	|    MOVE_LEFT    	|
| ARROW_RIGHT 	|    MOVE_RIGHT   	|
|      1      	|  Select lib SDL 	|
|      2      	| Select lib SFML 	|
|      3      	| Select lib FLTK 	|
|    ESCAPE    	|    Exit Game 	    |

#### Acceptable library names \<libname>

Library names are case insensitive and acceptable names are

	sdl
	fltk
	sfml

#### Acceptable dimensions

There's only 3 acceptable dimensions

	600x480, 900x600 and 1080x780

