#! /bin/bash

# (tempConv temp scale)
# ---------------------
# This function converts temperatures between Fahrenheit and Celcius,
#    where the user provides a temperature (as an integer) and either an F or C
#    to indicate whether the temperature was given in Fahrenheit or Celcius.
#
# The function then computes and displays the temperature on the opposite scale,
#    with all temperatures rounded to integers.
#
# e.g. if the user wanted to convert 100 degrees Celsius to Fahrenheit they would use
#       tempConv 100 C
#    and the resulting output would be:
#       100 degrees celsius is 212 degrees fahrenheit.
#
# Temperatures can be positive or negative, and the C or F can be supplied
#    in upper or lowercase.
#
function tempConv()
{

   E_ARGnum=222;
   E_TEMPint=123;
   E_SCALE=7733;
   if [$# -ne 2]; then
	   echo "Usage: need to have exactly 2 arguements" >&2
	   
   else 
   fi
   # obtain the initial temperature and scale used
   local tempIn=$1
   local tempScale=$2

   # determine the scales used
   # (treat both as fahrenheit, then switch whichever one isn't)
   local scaleIn="fahrenheit"
   local scaleOut="fahrenheit"
   if [ $tempScale = "F" ] ; then
      scaleOut="celsius"
   elif [ $tempScale = "f" ] ; then
      scaleOut="celsius"
   elif [ $tempScale = "C" ] ; then
      scaleIn="celsius"
   elif [ $tempScale = "c" ] ; then
      scaleIn="celsius"
   fi

   # compute the converted temperature
   local tempOut=$tempIn
   if [ $scaleOut = "celsius" ] ; then
      let tempOut="(5*($tempOut-32))/9"
   else
      let tempOut=($tempOut*9)/5
      let tempOut=$tempOut+32
   fi

   # display the results
   printf "%d degrees %s is %d degrees %s\n" $tempIn $scaleIn $tempOut $scaleOut
}

