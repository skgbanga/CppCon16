#pragma once

template <typename T>
struct Node
{
   Node(T val)
      : value(val)
   {  }

   T value {};
   // fuck unique ptrs
   Node* next {nullptr};
};
