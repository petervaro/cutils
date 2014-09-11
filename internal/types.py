## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.95.968 (20140904)                       ##
##                                                                            ##
##                          File: internal/types.py                           ##
##                                                                            ##
##   For more information about the project, visit <http://www.cutils.org>.   ##
##                       Copyright (C) 2014 Peter Varo                        ##
##                                                                            ##
##  This program is free software: you can redistribute it and/or modify it   ##
##   under the terms of the GNU General Public License as published by the    ##
##       Free Software Foundation, either version 3 of the License, or        ##
##                    (at your option) any later version.                     ##
##                                                                            ##
##    This program is distributed in the hope that it will be useful, but     ##
##         WITHOUT ANY WARRANTY; without even the implied warranty of         ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            ##
##            See the GNU General Public License for more details.            ##
##                                                                            ##
##     You should have received a copy of the GNU General Public License      ##
##     along with this program, most likely a file in the root directory,     ##
##        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        ##
##                                                                            ##
######################################################################## INFO ##

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
C_TYPES = (('char'              , 'c'  , ''   ),
           ('signed char'       , 'c'  , ''   ),
           ('unsigned char'     , 'u'  , ''   ),
           ('char*'             , 's'  , ''   ),
           ('short'             , 'hd' , ''   ),
           ('unsigned short'    , 'hu' , ''   ),
           ('int'               , 'd'  , ''   ),
           ('unsigned int'      , 'u'  , 'u'  ),
           ('long'              , 'ld' , 'l'  ),
           ('unsigned long'     , 'lu' , 'ul' ),
           ('long long'         , 'lld', 'll' ),
           ('unsigned long long', 'llu', 'ull'),
           ('float'             , 'f'  , 'f'  ),
           ('double'            , 'lf' , ''   ),
           ('long double'       , 'Lf' , ''   ),
           ('bool'              , 'd'  , ''   ),
           ('size_t'            , 'zu' , ''   ),
           ('ptrdiff_t'         , 'td' , ''   ))

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# TODO: Finish OpenGL types, create formatting functions for them
#       (And actually design the whole extension system of cutils)
#       http://www.opengl.org/wiki/OpenGL_Type
OPENGL_TYPES =(('GLboolean​',  '', ''),
               ('GLbyte​',     '', ''),
               ('GLubyte​',    '', ''),
               ('GLshort​',    '', ''),
               ('GLushort​',   '', ''),
               ('GLint​',      '', ''),
               ('GLuint​',     '', ''),
               ('GLfixed​',    '', ''),
               ('GLint64​',    '', ''),
               ('GLuint64​',   '', ''),
               ('GLsizei​',    '', ''),
               ('GLenum​',     '', ''),
               ('GLintptr​',   '', ''),
               ('GLsizeiptr​', '', ''),
               ('GLsync​',     '', ''),
               ('GLbitfield​', '', ''),
               ('GLhalf​',     '', ''),
               ('GLfloat​',    '', ''),
               ('GLclampf​',   '', ''),
               ('GLdouble​',   '', ''),
               ('GLclampd​',   '', ''))
