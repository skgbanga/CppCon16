#pragma once

#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>

#include <iostream>

bool is_power_of_2 (std::size_t x)
{
   return ((x & (~x + 1)) == x);
}

template <std::size_t N>
std::size_t highest_bit(const std::bitset<N>& bits)
{
   std::size_t ret = 0;
   for (std::size_t i = 0; i < N; ++i)
   {
      if (bits.test(i))
         ret = i;
   }
   return ret;
}

template <std::size_t N>
bool all_below_set(const std::bitset<N>& bits, std::size_t bitno)
{
   for (std::size_t i = 0; i < bitno; ++i)
   {
      if (!bits.test(i))
         return false;
   }
   return true;
}

std::size_t inflection_pt(std::size_t bitno)
{
   std::size_t k = bitno - 2;
   assert(k >= 0);
   std::size_t num = 0;
   for (std::size_t i = 0; i <= k; ++i)
      num += std::pow(2, i);

   return num;
}

template <typename T>
void print_dfs(T* node)
{
   if (!node)
      return;

   // print the node value first
   std::cout << node->value_ << ' ';

   // print the children now
   print_dfs(node->left.get());
   print_dfs(node->right.get());
}

template <typename T>
void print_bfs(T* node)
{
   struct Impl
   {
      T* node = nullptr;
      std::size_t level = 0;
   };

   if (!node)
      return;

   std::deque<Impl> qu; // doesn't invalidate the iterators
   qu.push_back({node, 0});

   std::size_t cur_level = 0;

   while (qu.size() != 0)
   {
      auto fr = qu.front();
      auto* n = fr.node;
      auto l = fr.level;

      // print the value
      if (cur_level != l)
      {
         std::cout << '\n';
         cur_level = l;
      }
      std::cout  << n->value_ << ' ';

      // add to the queue
      if (n->left)
         qu.push_back({n->left.get(), l + 1});

      if (n->right)
         qu.push_back({n->right.get(), l + 1});

      qu.pop_front();
   }
   std::cout << std::endl;
}
