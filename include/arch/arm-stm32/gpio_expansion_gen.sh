#!/bin/bash

FILE=./gpio_expansion.h

echo "#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_ARM_STM32_GPIO_EXP_H" > $FILE
echo "#define ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_ARM_STM32_GPIO_EXP_H" >> $FILE

echo "" >> $FILE
echo "/* Auto-generated file. Edit at your own risk. */" >> $FILE
echo "" >> $FILE

for i in `echo {A..H}`;
do
        for j in `echo {0..15}`;
        do
                echo "#define GP$i$j GPIO$i, RCC_APB2Periph_GPIO$i, $j" >> $FILE
        done
        echo "" >> $FILE
done

echo "" >> $FILE

echo "#endif" >> $FILE
