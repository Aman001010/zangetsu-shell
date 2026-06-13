#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  bool loop_check=true;
  while (loop_check == true){
  std::cout << "$ ";
  std::string input;
  std::getline(std::cin, input);
  
  if (input == "exit"){
   loop_check=false;
   break;
  }
  std::cout << input+": command not found"<<std::endl;
  

  }
}
