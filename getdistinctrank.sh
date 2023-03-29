#!/bin/bash

# to over come the single quote problem  this gets me the correct line

# $ awk -F" " '{ printf("{x:\x27%s\x27, y:%s}\n",$1, $2) }' newfile

stockslist=`cat snp.txt`

for stock in $stockslist
do

   #echo $stock

   echo "select distinct stockrank, date, stockSymbol , stockprice  from zacks_snp where stockSymbol=\"$stock\""

done
