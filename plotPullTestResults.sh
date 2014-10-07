#!/bin/bash

E_BADARGS=65

if [ ! -n "$1" ]
then
    echo "Usage: `basename $0` datafile.csv"
    echo
    echo "Plot results from pull tester result file"
    exit $E_BADARGS
fi

tempfilename=`basename $0`
TMPFILE=`mktemp -q /tmp/${tempfilename}.XXXXXX`
if [ $? -ne 0 ]; then
    echo "$0: Can't create temp file, exiting..."
    exit 1
fi

echo $TMPFILE

# convert csv files from DOS to Unix file format
awk '{ sub(/\r$/,"") };1' $1 > $TMPFILE

# split files
NFILES=`awk -v tmpfile="$TMPFILE" 'BEGIN { f=tmpfile "" 0; } /Count of Lot/ { f=tmpfile "" ++i; } { print > f; } END { print i; }' $TMPFILE`
echo $NFILES

# now extract the data from csv and plot the data using root
for ((i=1; i<=NFILES; i++))
do
    echo $i
    ./transformPullTest.awk ${TMPFILE}$i > ${TMPFILE}$i.dat
    root -b -q "plotPullTest.C+(\"${TMPFILE}$i.dat\")"
    mv plotPullTest.pdf plotPullTest_$i.pdf
    rm ${TMPFILE}$i ${TMPFILE}$i.dat
done

rm $TMPFILE

