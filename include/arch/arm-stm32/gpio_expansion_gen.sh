#!/bin/bash

FILE=./gpio_expansion_stm32f4.h

echo "#ifndef ANTARES_LIB_CEREBELLUM_ARCH_ARM_STM32_GPIO_EXP_H" > $FILE
echo "#define ANTARES_LIB_CEREBELLUM_ARCH_ARM_STM32_GPIO_EXP_H" >> $FILE

echo "" >> $FILE
echo "/* Auto-generated file. Edit at your own risk. */" >> $FILE
echo "" >> $FILE

for i in `echo {A..H}`;
do
        for j in `echo {0..15}`;
        do
                echo -e "#define GP$i$j\t GPIO$i,\t RCC_AHB1Periph_GPIO$i,\t $j" >> $FILE
        done
        echo "" >> $FILE
done

echo "" >> $FILE

echo "#endif" >> $FILE
