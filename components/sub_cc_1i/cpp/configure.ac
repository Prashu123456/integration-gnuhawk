#
# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
# 
# This file is part of GNUHAWK.
# 
# GNUHAWK is free software: you can redistribute it and/or modify is under the 
# terms of the GNU General Public License as published by the Free Software 
# Foundation, either version 3 of the License, or (at your option) any later 
# version.
# 
# GNUHAWK is distributed in the hope that it will be useful, but WITHOUT ANY 
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
# A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with 
# this program.  If not, see http://www.gnu.org/licenses/.
#

AC_INIT(sub_cc_1i, 1.0.0)
AM_INIT_AUTOMAKE(nostdinc)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

AC_CORBA_ORB
OSSIE_CHECK_OSSIE
OSSIE_SDRROOT_AS_PREFIX

GNUHAWK_PKG_CONFIG([${GHAWK_DIR}])

PKG_CHECK_MODULES([PROJECTDEPS], [ossie >= 1.10 omniORB4 >= 4.1.0 ] )
PKG_CHECK_MODULES([INTERFACEDEPS], [bulkio >= 1.0 bulkioInterfaces >= 1.10])

OSSIE_ENABLE_LOG4CXX
AX_BOOST_BASE([1.41])
AX_BOOST_THREAD
AX_BOOST_SYSTEM

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
