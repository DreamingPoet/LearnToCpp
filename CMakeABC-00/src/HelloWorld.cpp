#include <iostream>
#include <doodle/doodle.h>

int main(int argc, char *argv[]){

   std::cout << doodle::get_lib_name() << std::endl;
   std::cout << doodle::random_int() << std::endl;
   return 0;
}