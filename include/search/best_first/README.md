# best_first

This namespace is mainly for example. Many search algorithms can be implemented in the context of "best first search" through customizing a sorting function f for a priority queue.

You may notice that it seems the compare methods to define that sorting function are somewhat counter intuitive, that is due to how stl's [priority queue](https://en.cppreference.com/w/cpp/container/priority_queue) works:

>Note that the Compare parameter is defined such that it returns true if its first argument comes before its second argument in a weak ordering. But because the priority queue outputs largest elements first, the elements that "come before" are actually output last. That is, the front of the queue contains the "last" element according to the weak ordering imposed by Compare. 
