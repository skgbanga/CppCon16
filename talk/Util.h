#pragma once

#include <iostream>

// Step to the next node
template <typename T>
T* transformation(T* node)
{
   return node->next;
}

// check whether you have reached the end
template <typename T>
bool predicate(T* node)
{
   return (node != nullptr);
}

// find the collision point
template <typename T>
T* collision_point(T* head)
   // ideally should pass the transformation and predicate as function arguments
{
   if (!predicate(head))
      return head;

   auto slow = head;
   auto fast = transformation(head);
   while (fast != slow)
   {
      // move slow by one step
      slow = transformation(slow);

      // move fast by two steps
      if (!predicate(fast)) // haven't checked predicate for fast so far
         return fast;
      fast = transformation(fast);
      if (!predicate(fast))
         return fast;
      fast = transformation(fast);
   }

   // post condition - return value is either terminal point or if there is a loop then
   // it is the collision point
   return fast;
}

template <typename T>
bool terminating(T* head)
{
   return !predicate(collision_point(head));
}

template <typename T>
bool is_circular(T* head)
{
   auto y = collision_point(head);
   return predicate(y) && (head == y);
}

template <typename T>
T* convergant_point(T* node1, T* node2)
{
   // pre-condition: there should exist a convergant point! duh
   while (node1 != node2)
   {
      node1 = transformation(node1);
      node2 = transformation(node2);
   }

   return node1;
}

template <typename T>
T* connection_point(T* head)
{
   auto y = collision_point(head);
   if (!predicate(y))
      return y;

   // check the equations to see why this is working
   return convergant_point(head, transformation(y));
}

template <typename T>
// assuming distance type is int
// node2 is reachable from node1
int distance(T* node1, T* node2)
{
   int d = 0;
   while (node2 != node1)
   {
      node1 = transformation(node1);
      ++d;
   }
   return d;
}

template <typename T>
// assume distance type is int
std::pair<int, int> orbit_structure(T* head)
{
   auto y = connection_point(head);
   int h = distance(head, y); // distance from head to connection point - handle length

   int c = 0;
   if (predicate(y))
      c = distance(transformation(y), y);

   return {h, c};
}

template <typename T>
T* advance(T* head, int n)
{
   // pre-condition: n should be smaller than length of the list
   while (--n)
   {
      head = head->next;
   }
   return head;
}

template <typename T>
void print_list(T* head)
{
   while (head)
   {
      std::cout << head->value << ' ';
      head = head->next;
   }
   std::cout << "\n\n";
}

template <typename T>
void allocate_list(T* head, int num)
{
   for (int i = 2; i < num; ++i)
   {
      auto* node = new T(i);
      head->next = node;
      head = node;
   }
}
