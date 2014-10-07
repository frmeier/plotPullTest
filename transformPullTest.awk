#!/usr/bin/awk -f

BEGIN {
# Check arguments
    if (ARGC < 1) {
	print "Argument error!";
	exit(1);
    }
    FS=";";
    RDFLAG=0;
    IDTEXT="bla";
}

/Count of Lot/ { RDFLAG=0; }

#/User/ { print "User", $5; }
/HDI type/ { printf "%s ", $5; }
/work order \+ date code/ { printf "%s ", $5; }
/S\/N/ { IDTEXT+=" "+$5; printf "%s ", $5; }
/ROC position/ { IDTEXT+=" "+$5; printf "%s", $5;}

{
    if (RDFLAG==1) {
	gradeno="";
	grade=$8;
	if (grade=="Lift Off 1") gradeno=1;
	if (grade=="Heel Break 1") gradeno=2;
	if (grade=="Wire Break") gradeno=3;
	if (grade=="Heel Break 2") gradeno=4;
	if (grade=="Lift Off 2") gradeno=5;
#print $4,$6,gradeno,grade;
	print $6,gradeno;
    }
}

/Module;Bond;Results;Type;Grade;Comment/ {
    RDFLAG=1;
    printf "\n";
}

