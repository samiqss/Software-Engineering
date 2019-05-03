#! /bin/bash


# task: to create a script named searchTrash.sh
#       that allows the user to check the trash and see if
#       it contains any of their material from a specified
#       course and repository

#
# usage:
#    the user is able to enter the command
#        ./searchTrash.sh courseId assignmentName
#    e.g. to search for course csci200 the user would enter
#        ./searchTrash.sh csci200 lab1
#
# behaviour:
#    the script will then perform the appropriate commands to
#        get a list of what they have in the trash and pipe that
#        through grep for both the specified course and then
#        the specified repository
#    e.g. for csci200 lab1 it would display the results of
#        ssh csci D list-trash | grep csci200 | grep lab1
#
# exception handling:
#    if an incorrect number of command line arguments is provided
#       a suitable error message is displayed and the script ends
#    the command must be run from the core directory for the course,
#       e.g. ~/csci200 in the example above, otherwise the script
#       should generate an error message and terminate
#
# NOTES/TESTING AIDS:
# -------------------
#    if you want to experiment with your script, there is an extra csci265
#       repository posted that you can attempt forking/cloning: trashExpt
#    remember you can move something from your central repo to the trash with:
#       ssh csci D trash csci265/$user/trashExpt
#       (or whatever repository you actually trashed)
#

function searchTrash()
{
	#checks for correct number of command line args
	if [ $# -ne 2 ]; then 
		echo "Error: incorrect number of command line arguments provided"
		echo "correct use is to provide a class and repo for that class"
		echo "example : searchTrash.sh csci200 lab1
	else
		local class=$1
		local repo=$2
		
		#error detected flag
		local errorDetected=0

		#check if its run from the core directory of the course
		local re='^~[/]csci[0-9]+$'
		local home=~
		local core=$home/$class
		if ! [[ $ =~ $re ]]; then 
			echo "Error: not in right path, need to be in core directory for the course"
			echo "e.g. ~/csci200"
			errorDetected=1

		else 
			#checks if the repository from that course is in trash\
			ssh csci D list-trash | grep csci265 | grep trashExpt
		fi

		
	
		
	fi

}

searchTrash $@
