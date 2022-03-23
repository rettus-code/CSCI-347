#include <stdio.h>
#include <pwd.h>
 
int main(int argc, char const *argv[])
{
   struct passwd *p;
   int count;
   while((p = getpwent())) {
       printf("User Name:  %s\n", p->pw_name);
   }
   return 0;
}
