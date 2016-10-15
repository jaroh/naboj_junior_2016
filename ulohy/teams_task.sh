#!/bin/bash

roomlist=`awk -F";" '{print $3;}' < $1 | sort -u | sed ':a;N;$!ba;s/\n/ /g'`

rm -f $2

for room in $roomlist; do
  lng=`awk -F";" '($3=='$room') {print $5;}'< $1 | sort -u`
  echo "\$(OUT)/zadani-"$room".pdf: zadani.tex \$(SERIEDEP) \$(TEAMS)/teams-"$room".tex" >> $2
  if [ "$lng" = "1" ]; then
    echo -e "\t\$(XELATEX_PROBSSK)" >> $2
    echo -e "\t\$(XELATEX_PROBSSK)" >> $2
  elif [ "$lng" = "2" ]; then
    echo -e "\t\$(XELATEX_PROBS)" >> $2
    echo -e "\t\$(XELATEX_PROBS)" >> $2
  fi
  echo "" >> $2
  echo "\$(OUT)/zadani-"$room"p.pdf: zadani.tex \$(SERIEDEP) \$(TEAMS)/teams-"$room".tex" >> $2
  if [ "$lng" = "1" ]; then
    echo -e "\t\$(XELATEX_PROBSTSK)" >> $2
    echo -e "\t\$(XELATEX_PROBSTSK)" >> $2
  elif [ "$lng" = "2" ]; then
    echo -e "\t\$(XELATEX_PROBST)" >> $2
    echo -e "\t\$(XELATEX_PROBST)" >> $2
  fi
  echo "" >> $2
done



