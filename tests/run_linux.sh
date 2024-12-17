#!/bin/sh
export LD_LIBRARY_PATH=./lib
export LD_PRELOAD=libft_malloc.so
$@
