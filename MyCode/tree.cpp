#include "util.h"

#include <iostream>
#include <memory>
#include <cmath>

// balanced binary tree (this is not a search tree!)
template <typename T>
class Tree
{
   private:
   struct Node; // forward declare
   Node root_ {T{}}; // allocating one node before - hey, it is my tree!
   std::size_t num_nodes_ = 1;

   public:
   void add_node(T val)
   {
      add_node_impl(val, root_, num_nodes_);
      ++num_nodes_;
   }

   void print()
   {
      print_dfs(&root_);
      std::cout << std::endl;
   }

   void pretty_print()
   {
      print_bfs(&root_);
   }

   private:
   struct Node
   {
      Node(T val)
         : value_(val)
      {  }
      /* { */
      /*    std::cout << "ctor called for " << value_ << std::endl; */
      /* } */
      /* ~Node() { std::cout << "dtor called for " << value_ << std::endl; } */
      std::unique_ptr<Node> left = nullptr;
      std::unique_ptr<Node> right = nullptr;

      T value_;
   };

   void add_node_impl(T val, Node& parent, std::size_t nodes)
   {
      // base cases: 1 and 2
      if (nodes == 1)
      {
         parent.left = std::make_unique<Node>(val);
         return;
      }

      if (nodes == 2)
      {
         parent.right = std::make_unique<Node>(val);
         return;
      }

      // recursive step - choose which side to go on
      std::bitset<sizeof(std::size_t) * 8> bits (nodes);
      auto high = highest_bit(bits); // starts from zero

      // reset the highest bit as we don't need it anymore
      // helps in passing the decreased number of nodes to recursive calls as well
      bits.reset(high);
      std::size_t rnodes = bits.to_ullong();

      // if all the bits below highest bit are set, then we need to go left
      if (all_below_set(bits, high))
         return add_node_impl(val, *parent.left.get(), rnodes);

      // calculate the inflection point based on high bit
      auto inflection = inflection_pt(high);

      if (rnodes < inflection) // we have to go right with pow(2, )
         return add_node_impl(val, *parent.left.get(), rnodes + std::pow(2, high - 1));

      return add_node_impl(val, *parent.right.get(), rnodes);
   }
};

int main(int argc, char *argv[])
{
   if (argc != 2)
      return -1;

   int num = std::atoi(argv[1]);

   Tree<int> tree {};
   for (int i = 1; i < num; ++i)
      tree.add_node(i);

   /* tree.pretty_print(); */
   return 0;
}
