#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.725 (20140821)                       ##
##                                                                            ##
##                               File: setup.py                               ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

from distutils.core import setup

setup(name='cutils',
      version='0.8.90',
      description='Modern and Lightweight C Utilities',
      author='Peter Varo',
      author_email='petervaro@sketchandprototype.com',
      license='MIT',
      platforms='Any',
      url='http://www.cutils.org',
      package_dir={'': 'pycutils'},
      packages=['cutils', 'cutils.internal'])
