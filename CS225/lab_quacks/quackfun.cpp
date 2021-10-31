/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */
using namespace std; //for queue and stack
#include <iostream>
namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
  if (s.size() == 0) {
    return 0;
  }
  
  T top_node = s.top();
  
  s.pop();
  T sum_temp = sum(s) + top_node;
  s.push(top_node);
  return (sum_temp); 
  
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{   
    
    if (input.size() == 0) {
      return true;
    }
    
    if (input.front() == ']') {
      return false;
    }
    
    stack<char> brackets;
    
    for (size_t i = 0; i < input.size(); i++) {
      
      if (input.front() == '[') {
        brackets.push('[');
        input.push('[');
        input.pop();
      } else if (input.front() == ']') {
        
        if (brackets.size() == 0) {
          return false;
        }
        brackets.pop();
        input.push(']');
        input.pop();
        
      } else { //non bracket char
        input.push(input.front());
        input.pop();
      }
    }

    if (brackets.size() == 0) {
      return true;
    }
    return false;
  
    /*
    if (input.size() == 0) {
      return true;
    }
    
    if (input.front() == ']') {
      return false;
    }
    
    char at_front = '.';
    string brackets = "";
    
    while (!input.empty()) {
      at_front = input.front();
      
      if (at_front != '[' || at_front != ']') {
        input.pop();
      } else {
        brackets = brackets + at_front;
        input.pop();
      }
    }
    
    if (brackets.length()%2 != 0) {
      return false;
    }
    
    while (brackets.length() != 0) {
      if (brackets.length() == 2 && (brackets.at(0) == '[' && brackets.at(1) == ']')) {
        brackets = "";
      } else if (brackets.length() == 2) {
        return false;
      } else if (brackets.at(0) == '[' && brackets.at(1) == ']'){
        brackets = brackets.substr(2);
      } else if (brackets.at(0) == '[' && brackets.at(brackets.length() -1) == ']') {
        brackets.substr(1, brackets.length() - 1);
      } else {
        return false;
      }
    }
    
    return true;*/
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<int> reverse;
    queue<int> same_order;
    queue<int> correct_order;
    unsigned long iterated_elements = 1;
    
    while (q.size() != 0) {
      
      for (size_t i = 0; i < iterated_elements; i++) {
        if (iterated_elements % 2 == 1) { // same order - queue
          if(q.size() == 0) {
            break;
          }
          same_order.push(q.front());
          q.pop();
          
        } else { // reverse - stack
          if(q.size() == 0) {
            break;
          }
          reverse.push(q.front());
          q.pop();
        }
      }
      
      
      if (iterated_elements % 2 == 1) { // same order - queue
        while (same_order.size() != 0) {
          correct_order.push(same_order.front());
          same_order.pop();
        }
      } else { // reverse - stack
        while (reverse.size() != 0) {
          correct_order.push(reverse.top());
          reverse.pop();
        }
      }
      iterated_elements++;
    }
    
    q=correct_order;
}

}
