b=1
date >> series
while `test $b -le 10`
do
   date >> counter
   (cat coverpage; cat counter | wc -l) > uniquecover
   (cat coverpage; cat series | wc -l; echo; echo -n 'S/N '; cat counter | wc -l; echo; date) > uniquecover
   (cat coverpage; cat series | wc -l; echo -n 'NO. '; cat counter | wc -l; date) > uniquecover
   cat -u uniquecover >> /dev/lp
   cat -u blankpage >> /dev/lp

   i=1
   while `test $i -le 20`; do
      a.out > mandout
      if test `sed -n '4,$p' mandout | wc -w` -gt 3
      then
         cat mandout
         cat -u mandout > /dev/lp
         i=`expr $i + 1`
      else
         cp mandout mandout.blank
      fi
      done

   cat -u blankpage >> /dev/lp
   cat -u lastpage >> /dev/lp
   b=`expr $b + 1`
done
         echo "DEBUG: blank skipped..."
