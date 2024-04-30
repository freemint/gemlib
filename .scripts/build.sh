#!/bin/bash -eux
# -e: Exit immediately if a command exits with a non-zero status.
# -u: Treat unset variables as an error when substituting.
# -x: Display expanded script commands

make && make DESTDIR="${INSTALL_DIR}" PREFIX=/usr install

find "${INSTALL_DIR}" -type f \( -name '*.a' -o -name '*.o' \) -exec ${CROSS_TOOL}-strip -S -X -w -N '.L[0-9]*' {} \;
