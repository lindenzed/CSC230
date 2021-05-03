// Demonstration of macro expansion, including the ability to generate
// lots of code.

#define ABSDIFF(a,b) \
((a)>(b) ? (a)-(b) : (b)-(a))

int main()
{
   int x;

   // Expansion to something small
   x = ABSDIFF(5, 35);

   // Expansion to something larger
   x = ABSDIFF(70, ABSDIFF(5, 35));

   return 0;
}
