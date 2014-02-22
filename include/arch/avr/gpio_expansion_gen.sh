#!/bin/bash

FILE=./gpio_expansion.h

echo "#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_EXP_H" > $FILE
echo "#define ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_EXP_H" >> $FILE

echo "" >> $FILE
echo "/* Auto-generated file. Edit at your own risk. */" >> $FILE
echo "" >> $FILE

for i in `echo {A..H}`;
do
        for j in `echo {0..7}`;
        do
                echo -e "#define GP$i$j\t PORT$i,\t DDR$i,\t PIN$i,\t $j" >> $FILE
        done
        echo "" >> $FILE
done

echo "" >> $FILE

echo "#endif" >> $FILE
