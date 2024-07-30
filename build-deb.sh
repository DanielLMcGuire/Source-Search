#!/bin/bash

# Check if the version argument is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <version>"
  exit 1
fi

VERSION=$1
PACKAGE_NAME="sourcesearch"
PACKAGE_DIR=".DEBIAN"

# Check if the required directories and files exist
if [ ! -d "$PACKAGE_DIR" ] || [ ! -d "$PACKAGE_DIR/DEBIAN" ]; then
  echo "Error: .DEBIAN directory does not exist or is not correctly structured."
  exit 1
fi

# Build the .deb package
dpkg-deb --build "$PACKAGE_DIR"

# Rename the package to include version
mv "${PACKAGE_DIR}.deb" "${PACKAGE_NAME}_${VERSION}.deb"

echo "Package ${PACKAGE_NAME}_${VERSION}.deb created successfully."
