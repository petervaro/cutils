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
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
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
