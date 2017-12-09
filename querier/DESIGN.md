# Aaron Svendsen and William Wolfe - Design for Querier

## Requirements

The TSE querier is a standalone program that reads the index file produced by the TSEindexer, and answers search queries submitted via stdin.

The querier shall:

1. execute from a command line with usage syntax
* ./querier pageDirectory indexFilename
* where pageDirectory is a directory produced by the crawler, and
* where indexFilename is an index file produced by the indexer.
2. load the index from indexFilename into an internal data structure.

3. read search queries from stdin, one per line, until EOF.
   1. clean and parse each query according to the syntax described below.
   2. print the ‘clean’ query for user to see.
   3. use the index to identify the set of documents that satisfy the query, as descr	ibed below.
   4. if no documents satisfy the query, print No documents match.
   5. otherwise, rank the resulting set of documents according to its score, as descr	ibed below, and print the set of documents in decreasing rank order; for each, lis	t the score, document ID and URL. (Obtain the URL by reading the first line of		the relevant document file from the pageDirectory.)
   The querier shall validate its command-line arguments:

* pageDirectory is a directory produced by the crawler, and
* indexFilename is the name of a readable file.

The querier may assume that the input directory and files follow the designated formats.

* pageDirectory has files named 1, 2, 3, …, without gaps.
* The content of document files in pageDirectory follow the format as defined in the crawler specs; thus your code (to read a document file) need not have extensive error checking.
* The content of the file named by indexFilename follows our Index file format; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

## Design

User Interface
* comand line with 2 arguments
* takes in from stdin words to search

Inputs and Outputs
* Input a crawler directory and a index file
* Outpus results from search

Functional Decomposition into modules
* Struct for idnum and scores 
* loop thorugh for and and shorten struct to include idnums with all words
* or all the resulting lists togehter

Pseudo Code-High Level
1. Parse and check arguments
2. take for stdin a line at a time
3  for each line check syntax
4. if syntax is incoreect print bad status for line
5. make first word into a struct of idnums and scores
6. if and then combine struct with info to next word
7. If or then make a new struct and combine in with subsequent ands
8. At the end combine all structs adding the scores because the are all separated by or
9. Print resultig scores and urls

Major Data Structures
* inverted hashtable
* counters
* struct that is a sorting list to hold idnums and pairs

## Implementation
1. Error Handling
 * returns errors for incorrect synatax and keeps running
 * returns error and exits for incorrect arguments
2. Data Structures
   * Hashtable to keep index
   * Counterslike data structure to keep scores and update scores
3. Pseudo Code
   1. Check args
   2. Open File
   3. Make Hashtable and fill it with words
      1. Get words from index file
      2. populate table
   4. close file
   5. while line is not null then readline
      6. check syntax of word
      	 1.if line is null or empty then return null
	 2. make lowercase
	 3. go through each word with space as delim
	 4. if word is and or or then set bool to false
	 5. if you get two and or ors in a row then return NULL
	 6. else it is word
	 7. make sure it is alpha
	 8. go to next word
	 9. If too many word the return null
      7. if correct syntax then find the query
      	 1. make array of objects
	 2. make all NULL
	 3. if the word is "and" "or" then skip
	 4. if "and" then combine
	 5. add all
	 6. print results using iterator
      8. return and print results
      9. free line
   10. free hashtable
   Pseudo Code for data structure:
	* Making a new orderlist:
		1.make a new list struct
		2.check to see if the given word is in the given hashtable, return null if not in the table
		3.call the counters_iterate for the apropriate word in the hastable and add the items to the new orderlist struct
	* Calling an "and" on the list:
		1.if the given list is null or the given word is not in the given hashtable, reutrn null
		2.iterate through the counter for the given word in the given hashtable. Compare each item in the counters to the orderlist items marking orderlist items that were in the counter and seting the score to the lowest score
		3.remove all items that were not marked and were therefore not in both lists then reset all marks to false;
	* Calling "or" on the list:
		1.loop through both lists combing the items that are in both lists into the left list
		2.loop through the right list and add any items that were in the right list but not in the left list to the left list
	* Calling delete on list:
		1.loop through the given list and free each node 
	* Calling iterate on list:
		1.loop through the list and call the given function on each node
		

## Testing Plan
Test new data module by making a fake hashtable and index file
Test each function in dat
Test each part when we build it
Check the syntax
Use the fuzzy thing to generate queries
Use querires to test program
