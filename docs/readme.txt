
SummaryL
We used the provided Malloc and Free code from class for this implementation.
Errors are printed from malloc with the calling file, function and line number.
Error are reported with the calling file and line number. 
Malloc doesn't expand the allocation space when the limit is reached. It instead prints
that it could not allocate any more space and gives the user where the malloc was attempted.

Complications:
When trying to deal with the fragmentation issue, we attempted to malloc backwards up the
heap for our smaller data structures. However this implementation did not work properly.
When running test 5, we would seg fault after allocation of 150 chars into our heap. 
We tried countering this seg fault with measures, such as making sure the pointer is within the
bounds of the static char array myblock, however these efforts proved fruitless.
We tried other things: making sure the root's prev was 0, checking if the patteren existed before
trying to use the pointer, not allocating backwards at the root, but these methods also failed.

Because of these complications, our Malloc doesn't handle the defragmentation problem. And does a forward malloc for all input.
