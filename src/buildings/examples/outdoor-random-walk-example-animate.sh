#!/bin/bash

# Copyright (c) 2019, University of Padova, Dep. of Information Engineering, SIGNET lab
# Copyright (c) 2021, University of Washington: animation extensions
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Authors: Michele Polese <michele.polese@gmail.com>
#          Tom Henderson <tomhend@uw.edu> (animation extensions)

#
#  Plot the trace generated by outdoor-random-walk-example.cc
#  in a manner that enables animation
#

# This Bash script is a variant of outdoor-random-walk-example.sh that
# generates a large number of PNG image files, one for each node position
# traced in the mobility trace file 'mobility-trace-example.mob'
#
# To run this script, ensure that 'mobility-trace-example.mob' and
# 'buildings.txt' file are present in the same directory.  The script
# will create a subdirectory named 'outdoor-random-walk-animation' and
# will generate 820 PNG files into that subdirectory.
# 
# The PNGs are named in increasing numerical order from '0000.png' to
# '0819.png'.  The images can be assembled into an animated gif file
# using a tool such as ImageMagick's convert utility, such as:
#
# $ convert -delay 100 -loop 0 *.png outdoor-random-walk-animation.gif
#
# For a similar script that produces a single EPS file of all locations
# traced, see 'outdoor-random-walk-example.sh'.

mkdir -p outdoor-random-walk-animation
cat mobility-trace-example.mob | awk -F " " '{ print $3 }' | awk -F "=" '{ print $2 }' | awk -F ":" '{ print $1" "$2 }' > mobility-trace-reduced.txt
n=0
while read p; do
    basename=$(printf "%04d" "$n")
    cat >plotcmds <<EOL
set terminal png
set output '$basename.png'
set view map
set xlabel 'X [m]'
set ylabel 'Y [m]'
set xrange [-25:1300]
set yrange [-25:800]
set style fill transparent solid 0.5
unset key
set style fill  transparent solid 0.35 noborder
set style circle radius 5
plot "<echo '$p'" with circles lc rgb "blue"
EOL
    gnuplot buildings.txt plotcmds
    rm plotcmds 
    mv $basename.png outdoor-random-walk-animation
    (( n++ ))
done < mobility-trace-reduced.txt
rm mobility-trace-reduced.txt
