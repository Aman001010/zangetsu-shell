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
  std::string firstword ="";
  int i=0;
  while(input[i]!=' '){
    firstword+=input[i];
    i++;
  }

  if (firstword =="echo"){

    int len = input.length();
    std::string output = input.substr(5,len+1);
    std::cout << output << std::endl;
  }
  else if(firstword=="type"){
        int len = input.length();
    std::string command = input.substr(5,len+1);
    if (command == "echo" | command == "type" | command == "exit"){
      std::cout<< command+" is a shell bulletin"<<std::endl;
    }
    else{
      std::cout<< command+": not found"<<std::endl;
    }
  }
  else{
  std::cout << input+": command not found"<<std::endl;
  }

  
}
}
