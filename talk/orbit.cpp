#include "Node.h"
#include "Util.h"

#include <tuple>

using NodeType = Node<int>;

int main(int argc, char *argv[])
{
   NodeType head(1);

   // ALLOCATE
   allocate_list(&head, 99);

   // PRINT
   std::cout << "List is" << "\n";
   print_list(&head);

   // CHECK LOOP
   auto ends = terminating(&head); // !predicate(collision_point(&head));
   if (ends)
      std::cout << "List reached an end! Unicorns!!\n\n";

   // CREATE LOOP
   auto some1 = advance(&head, 80);
   auto some2 = advance(&head, 22);

   // LINK
   some1->next = some2;

   // CHECK LOOP
   auto col_point = collision_point(&head);
   if (col_point)
      std::cout << "Loop detected! Hmph!\n\n";

   // FIND CONNECTION POINT
   auto con_pt = connection_point(&head);
   if (con_pt)
      std::cout << "Loop starts at " << con_pt->value << "\n\n";

   // GET HANDLE SIZE AND CIRCLE SIZE
   int h = 0; int c = 0;
   std::tie(h, c) = orbit_structure(&head);
   std::cout << "Handle size = " << h << ". Circle size = " << c << "\n\n";

   // FREE MEMORY?! CAN'T
   return 0;
}
