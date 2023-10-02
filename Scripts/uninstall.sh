#!/bin/bash

function fixpath() {
    case "$OSTYPE" in
        *linux*|*darwin*|*bsd*) echo "${1//\\/\/}" ;;
        *win*) echo "${1//\//\\}" ;;
    esac
}

case "$OSTYPE" in
    *linux*|*darwin*|*bsd*) cmake_install_prefix=/usr/local;;
    *win*)                  cmake_install_prefix="C:/Program Files";;
esac

installation_directory=$cmake_install_prefix/include/MySampler;
installation_directory=$(fixpath $installation_directory);

echo "deleting installation directory: $installation_directory";

rm -r $installation_directory;
