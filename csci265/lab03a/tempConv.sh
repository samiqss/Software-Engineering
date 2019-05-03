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
# The function displays an error messages and ends in any of the following cases:
#  - an incorrect number of arguments is supplied
#  - a non-integer value is provided for the temperature
#  - a scale other than F, f, C, or c is provided
#
function tempConv()
{
   # check for the correct number of arguments
   if [ $# -ne 2 ] ; then
      echo "Error: incorrect number of command line arguments provided"
      echo "   correct use is to provide a temperature and scale, e.g."
      echo "   tempConv 60 F"
   else
      # obtain the initial temperature and scale used
      local tempIn=$1
      local tempScale=$2

      # error detected flag
      local errorDetected=0

      # specify the pattern for a regex to match integers
      local re='^[+-]?[0-9]+$'

      # check the temperature is provided as an integer
      if ! [[ $tempIn =~ $re ]] ; then
         echo "Error: temperature ($tempIn) is not an integer"
         errorDetected=1

      # determine the scales used
      else
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
         else
            echo "Error: invalid scale used ($tempScale), you must use F, f, C, or c"
            errorDetected=1
         fi

         # if no error was detected then compute and display the results
         if [ $errorDetected -eq 0 ] ; then
            # compute the converted temperature
            local tempOut=$tempIn

            # from fahrenheit to celsius
            if [ $scaleOut = "celsius" ] ; then
               let tempOut="(5*($tempOut-32))/9"

            # from celsius to fahrenheit
            else
               let tempOut=($tempOut*9)/5
               let tempOut=$tempOut+32
            fi

            printf "%d degrees %s is %d degrees %s\n" $tempIn $scaleIn $tempOut $scaleOut
         fi
      fi
   fi
}

