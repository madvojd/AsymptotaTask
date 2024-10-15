main.cpp contains code for benchmarking the solution.
test.cpp contains unit tests, implemented using GoogleTest framework.

Book class contains all the bids and asks for a given Symbol.
Books class contains a "book" with all the symbols. It also has functionality for printing the best bids and asks for all symbols contained in the book.

As to handle large amount of data I used a simple implementation of a thread pool. 

There is a makefile which you can use to build the project.
