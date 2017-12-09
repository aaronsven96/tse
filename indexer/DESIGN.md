# Aaron Svendsen and William Wolfe Indexer Design

## Requirements Spec-from professor Kotz

The TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.

The indexer shall:

1. execute from a command line with usage syntax
* ./indexer pageDirectory indexFilename
* where pageDirectory is a directory produced by the crawler, and
* where indexFilename is the name of a file into which the index should be written.
2. read documents from the pageDirectory, each of which has a unique document ID,
* wherein the document id starts at 1 and increments for each new document,
* and the filename is of form pageDirectory/id,
* and the first line of the file is the URL,
* and the second line of the file is the depth,
* and the rest of the file is the page content.
3. build an inverted-index data structure mapping from words to (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and NormalizeWord before indexing.
4. create a file indexFilename and write the index to that file, in the format described below.

The indexer shall validate its command-line arguments:

* pageDirectory is a directory produced by the crawler (see below), and
* indexFilename is the name of a writeable file.

The indexer may assume that

* pageDirectory has files named 1, 2, 3, …, without gaps.
* The content of files in pageDirectory follow the format as defined in the crawler specs; thus your code (to create a WebPage by reading a file) need not have extensive error checking.

The index tester shall:

1. execute from a command line with usage syntax
* ./indextest oldIndexFilename newIndexFilename
* where oldIndexFilename is the name of a file produced by the indexer, and
* where newIndexFilename is the name of a file into which the index should be written.

2. load the index from the oldIndexFilename into an inverted-index data structure.
3. create a file newIndexFilename and write the index to that file, in the format described below.

It need not validate its command-line arguments other than to ensure that it receives precisely two arguments; it may simply try to open the oldIndexFilename for reading and, later, try to open the newIndexFilename for writing. You may use indextest.sh (provided) to verify that the output is identical to (or equivalent to) the input.

The index tester may assume that

* The content of the index file follows the format specified below; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

### Index file format

The indexer writes the inverted index to a file, and the querier reads the inverted index from a file; the file must be in the following format.

* one line per word, one word per line
* each line provides the word and one or more (docID, count) pairs, in the format
* word docID count [docID count]…
* where word is a string of lower-case letters,
* where docID is a positive non-zero integer,
* where count is a positive non-zero integer,
* where the word and integers are separated by spaces.

## Design Spec-some of it taken from prof Kotz lecture

1. The Indexer will use a command line interface

2. The indexer takes in a database of crawler files and prints an index

3. The crawler will use several data structures
* Hashtable with the words
** Hashtableuses a list
** data in the hashtable will be counters

4.High Level Pseudocode

Indexer

1. Process command line arguments
2. Initialize data structures
3. GO through each file of crawler output
* read words from file
* add words to hashtable
4. print words to file
5. delete data structures

Indextest
1. process command line arguments
2. initilize the data structures
3. open the input file
4. pull the words and data from the input file and insert into hashtable
5. create output file
6. iterate through hashtable putting data in output file
7. close files and delete data structures


## Implementation Spec

### Main Function
1. check arguments
2. Make Hashtable
3. fill hashtble
4. Open file to print
5. Print to file
6. file close
7. delete hashtable
8. return zero

### Check arguments
1. if there are not 3 arguments print error
2. if the first argument does not contain .crawler print error
3. if the second argument is not a writable file then print error message

### Check directory
1. Make a string that is the filename
2. try to open the invisible crawler file
3. if you suceed return true
4. if not return false

### checks for file
1. try to open the file
2. if you suceed print true
3. else print false

### fill hashtable

1. Open each file by going through thier filenames
2. get each word
3. make a counters object
4. add word to counters
5. puts the word form each file in a hashtable
6. if it cant insert then find the key and edit the counter
7. close the fileand go to file 

### print the info
1. iterate through the hashtable
2. print the key
3. iterate through the counters
4. print the count and id

### delete the hashtable
1. pass counter delete to the hashtable

###IndexTest
1. pass arguments to argument tester method to test if correct number of arguments
and first argument is a readable file
2. open the output file
3. iterate through each word in the input file
3. if the current string in the input file is a word and not a number, create a new counter table in the hashtable, else put the id number and the number of occurences in a node in the current counter
4. call hastable iterator with a function that outputs the contents of the table into the output file
5. close both the output file and input file, also free the hashtable

##Testing plan
1. Test the data structures
2. Test the iteraters
3. Test the code while we make it
4. Use valgrinds to find data leaks
5. Using Kotz testing functions
6. Test Everything



