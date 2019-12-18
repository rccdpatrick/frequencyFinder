# frequencyFinder
Team Member: 
Patrick Saade

Program Purpose: 
To read a text file and find the frequency of a given character or word given by the user. 
Will also return the location of the word/character from the text file (indexed by word).

Logic Behind Program:
The program incorporates a binary search tree to store the locations of the matched and unmatched words/characters that it finds.
What it does is if the word from the text file matches with what the user wants, it would go on the right side tree with the location
value. Otherwise, the failed matches would go onto the left side of the tree. From there, a search function would traverse the tree
and find all the matches that occured and return those values.

Version Number: 1.0
