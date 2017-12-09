# Indexer created by Aaron Svendsen and William Wolfe

## Compiling
See MakeFile and use make

## Command Line
indexer datapath file

indexer ../crawler/data index.txt

## Usage:
Use the indexer to print an index that shows the words present in the files of a
crawler data directory.


## Exit status
* Exit 0-Sucess
* Exit 1-wrong number of arguments
* Exit 2-the directory is incorrect
* Exit 3-cant write onto file

## Limitations
The hashtbale was of size 5 thousand. More words could slow it down.

## Assumptions
The data files must be formatted correctly
The directory must have .crawler
They must be words

# Indextest created by William Wolfe and Aaron Svendsen

## Compiling
Run make Test

## Command Line
Test inputfile output

##Exit status
* exit 0-sucsess
* exit 1-wrong number of arguments
* exit 3-not readable file for input file

## Limitations
the input and output file will be in different orders.
We found dificulty getting the indexsort.sh to work but we checked files and
they were both the same. Output file mustbe a creatable file. And input file must
be a valid output from indexer

## Assumptions
Output file mustbe a creatable file. And input file must
be a valid output from indexer.