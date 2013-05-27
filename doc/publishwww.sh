#! /bin/bash

if [ -n "$1" ]
then host=$1@scm.gforge.inria.fr
else host=scm.gforge.inria.fr
fi

scp ./www/*.php $host:/home/groups/sollya/htdocs/sollya-current/
scp ./www/sollyacss.css $host:/home/groups/sollya/htdocs/sollya-current/

