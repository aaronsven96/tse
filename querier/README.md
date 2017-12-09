# Querier created by Aaron Svendsen and William Wolfe

## Compiling
See MakeFile and use make

## Command Line
querier crawlerdata indexfile

querier data50 index

## Usage:
Use the querier to find urls that have word using and or syntax. Need an index file and cralwer directory


## Exit status
* Exit 0-Sucess
* Exit 1-wrong number of arguments
* Exit 2-the directory is incorrect
* Exit 3-cant read from file

## Limitations
I think there could be memory problems so a large amount of queries could
cause problems or a seg fault. We have some memory leaks.

## Assumptions