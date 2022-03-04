# Visuals
<img src='https://user-images.githubusercontent.com/94231603/156769068-a5bb8026-252f-4afd-aa41-cd6a07d7a3a8.PNG'  width="500" height="350">
<img src='https://user-images.githubusercontent.com/94231603/156769051-ccbae338-c4d8-452d-a932-7983b262bb1d.PNG' width="500">

# Word-Graphs!
We will be solving a puzzle that is made up of a list of words, we are given several english words. And our goal is to go from word A to word B by a series of one character substitutions, one character insertion or one character deletions.

# Data Structure Used
I have focused on using graphs. All the words we have given in words.txt we will set them inside a graph and connect them with words that have only 1 word differ. For example help is connected with hel,hell and belp. After that we will implement BFS(breadth first search) over the graph and find the shortest path from word A to word B thats if it exists!
