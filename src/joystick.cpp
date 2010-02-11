/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    
  based on my previous code which can be found here:
    http://lastlog.de/wiki/index.php/SDL-joystick and 
    http://lastlog.de/misc/sdl_joystick_demo.html
    
  http://de.wikibooks.org/wiki/SDL:_Joystick

    example2.cpp can be compiled with:
   	g++ example2.cpp -o example2 `sdl-config --libs` `sdl-config --cflags`

*/

#include "joystick.h"

joystick::joystick () {
	if ( SDL_InitSubSystem ( SDL_INIT_JOYSTICK ) < 0 )
	{
		fprintf ( stderr, "Unable to initialize Joystick: %s\n", SDL_GetError() );
		exit(1);
	}
	printf ( "%i joysticks found\n", SDL_NumJoysticks () );
	
	// TODO add check
	joy1 = SDL_JoystickOpen ( 0 );

	if ( joy1 == NULL ) {
		printf ( "SDL backend: could not open joystick\n" );
// 		exit(1);
	}

	printf ( "%i achsen\n", SDL_JoystickNumAxes ( joy1 ) );
	printf ( "%i rollbaelle\n", SDL_JoystickNumBalls ( joy1 ) );
	printf ( "%i heads\n", SDL_JoystickNumHats ( joy1 ) );
	printf ( "%i koepfe\n", SDL_JoystickNumButtons ( joy1 ) );

	//SDL_JoystickEventState (SDL_ENABLE);
	// this will alter the behaviour of the event queue of the sdl system
	SDL_JoystickEventState ( SDL_QUERY );
}

void joystick::joyupdate() {
  SDL_JoystickUpdate ();
}
