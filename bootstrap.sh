#!/bin/bash

echo "Cerebellum library bootstrap for Antares"

if [[ -n $ANTARES_INSTALL_DIR ]]; then
        echo "Installing library for Antares..."
        ln -sf `pwd`/src/ $ANTARES_INSTALL_DIR/src/lib/contrib/cerebellum
        ln -sf `pwd`/include/ $ANTARES_INSTALL_DIR/include/lib/cerebellum
        echo "Done."
else
        echo "Antares environment is not found!"
fi
