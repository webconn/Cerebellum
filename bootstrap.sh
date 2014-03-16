#!/bin/bash

echo "Cerebellum library bootstrap for Antares"

if [[ -n $ANTARES_INSTALL_DIR ]]; then

        if [[ -a $ANTARES_INSTALL_DIR/src/lib/contrib/cerebellum ]]; then
                echo "Looks like Cerebellum library is linked into Antares environment..."
                echo "Nothing to be done."
                exit
        fi

        echo "Installing library for Antares..."

        echo "Symlinking..."

        ln -sf `pwd`/src/ $ANTARES_INSTALL_DIR/src/lib/contrib/cerebellum
        ln -sf `pwd`/include/ $ANTARES_INSTALL_DIR/include/lib/cerebellum

        echo "Add kcnf info..."

        echo "source antares/src/lib/contrib/cerebellum/kcnf" >> $ANTARES_INSTALL_DIR/src/lib/contrib/kcnf

        echo "Done."
else
        echo "Antares environment is not found!"
        echo "Nothing to be done."
fi
