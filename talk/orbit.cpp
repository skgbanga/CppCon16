#include "Node.h"
#include "Util.h"

#include <tuple>

using NodeType = Node<int>;

int main(int argc, char *argv[])
{
   NodeType head(1);

   // allocate everything else
   allocate_list(&head, 99);

   // just print to verify everything is fine
   std::cout << "List is" << "\n";
   print_list(&head);

   // see if we have loop in our non-loop list. duh!
   auto ends = terminating(&head); // !prediate(collision_point(&head));
   if (ends)
      std::cout << "List reached an end! Unicorns!!\n\n";

   // create the loop
   auto some1 = advance(&head, 80);
   auto some2 = advance(&head, 22);

   // link them together
   some1->next = some2;

   auto col_point = collision_point(&head);
   if (col_point)
      std::cout << "Loop detected! Hmph!\n\n";

   // find the connection point
   auto con_pt = connection_point(&head);
   if (con_pt)
      std::cout << "Loop starts at " << con_pt->value << "\n\n";

   // get handle size and circle size
   int h = 0; int c = 0;
   std::tie(h, c) = orbit_structure(&head);
   std::cout << "Handle size = " << h << ". Circle size = " << c << "\n\n";

   // free memory? ha ha ha
   return 0;
}
