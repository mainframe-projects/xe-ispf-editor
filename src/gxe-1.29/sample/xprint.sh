# gxp is recomended ***********091215 
gxp $1 $2 $3 $4 $5 $6 $7 $8 $9 
exit
#sample shell to format and print text-file using xprint
#########################
#  xprint parm          #
#-ne:skip output escape sequence cmd
#-nu:skip output formfeed cmd
#-q-:output to stdout
#-l :line count/page  
#-c :char count/line
#########################
#  mpage  parm          #
#-1 :1 page/sheet
#-b :paper type  
#-o :toggle draw outline box(check current setting by "mpage -x") 
#-L :line count/page
#-W :char count/line
#-m30b:bottom margin is 30 point
#########################
qopt=0
for parm in $@
do
    case "$parm" in
    -[Qq]*)    qopt=1;;
    esac
done
#########################
COLXP=105
LINEXP=60
COLMPAGE=`expr $COLXP + 7`          #for lineno field width
LINEMPAGE=`expr $LINEXP + 3`        #for header/trailer lines
#########################
if  [ $qopt -eq 1 ]
then
	xprint -ne -nu -l$LINEXP -c$COLXP $1 $2 $3 $4 $5 $6 $7 $8 $9
else
	xprint -ne -q- -nu -l$LINEXP -c$COLXP $1 $2 $3 $4 $5 $6 $7 $8 $9 | mpage -1 -bA4 -o -m30b -W$COLMPAGE -L$LINEMPAGE | lpr
fi
