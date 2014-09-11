## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.95.959 (20140902)                       ##
##                                                                            ##
##                          File: internal/output.py                          ##
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

# Import cutils modules
from generator import methods, PseudoFunction

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
BASE_NAME = ''
PREFIX = 'cutils_cout'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_ASSOC = '{ASSOCTYPE}:{PREFIX}_{ASSOCWORD}_{NAME}'

#------------------------------------------------------------------------------#
chr_print = PseudoFunction('print', 1, 'char')
chr_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
sch_print = PseudoFunction('print', 1, 'signed char')
sch_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
uch_print = PseudoFunction('print', 1, 'unsigned char')
uch_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
chp_print = PseudoFunction('print', 1, 'char*')
chp_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
sht_print = PseudoFunction('print', 1, 'short')
sht_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ush_print = PseudoFunction('print', 1, 'unsigned short')
ush_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
int_print = PseudoFunction('print', 1, 'int')
int_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
uin_print = PseudoFunction('print', 1, 'unsigned int')
uin_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
lon_print = PseudoFunction('print', 1, 'long')
lon_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ulo_print = PseudoFunction('print', 1, 'unsigned long')
ulo_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
llo_print = PseudoFunction('print', 1, 'long long')
llo_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ull_print = PseudoFunction('print', 1, 'unsigned long long')
ull_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
flo_print = PseudoFunction('print', 1, 'float')
flo_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
dbl_print = PseudoFunction('print', 1, 'double')
dbl_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ldb_print = PseudoFunction('print', 1, 'long double')
ldb_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
bol_print = PseudoFunction('print', 1, 'bool')
bol_print.generics = _ASSOC

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
vpt_print = PseudoFunction('print', 1, 'void*')
vpt_print.generics = _ASSOC

#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(base_name=BASE_NAME,
            module_prefix=PREFIX,
            macros_dict=macros_dict,
            functions=(chr_print, sch_print, uch_print, chp_print, sht_print,
                       ush_print, int_print, uin_print, lon_print, ulo_print,
                       llo_print, ull_print, flo_print, dbl_print, ldb_print,
                       bol_print, vpt_print))
