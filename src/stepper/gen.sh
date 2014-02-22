#!/bin/bash

FILE=val_table.inc

MIN_VALUE=128
CONVERTER=60000000
DIMENSION=100

MAX_SPEED=$(($CONVERTER / $MIN_VALUE))
SPEED_STEP=$(($MAX_SPEED / $DIMENSION))

echo "static int16_t val_table[] = {" > $FILE
echo -e "\t0," >> $FILE

for i in `seq $SPEED_STEP $SPEED_STEP $MAX_SPEED`;
do
        echo -e "\t"$(($CONVERTER / $i + 16))"," >> $FILE
done

echo "};" >> $FILE
