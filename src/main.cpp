#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

std::string path_file(const std::string& command){
  // the below is responsible of getting the entire path to search for the command and find out if it exists in the OS or not

      int count=0; //for the found/not found of executable when searching
      
      if(const char* full_path = std::getenv("PATH")){ // gives PATH to full_path

        //stringstream object ss created, stringstream allows us to either convert string character type from say string to int OR  (the use here) to parse the string 
        std::stringstream ss(full_path);

        std::string directory;
        std::string exepath;
        

        while(std::getline(ss,directory,':')){//getline is used for taking string input due to the delimeter being by default '\n' delimeter here we read ss till it reaches : and add that to directory

          if(directory.empty()){ //this ensures that if the striing has something like ::usr/bin:... the empty path (:: part) doesn't come in the modified version since that would make the path //usr/bin which is obv invalid 
            continue;
          }
          std::string filepath = directory+"/"+command;
          
          //now I need to take this filepath and search in it if executable exists

          if(access(filepath.c_str(),X_OK)==0){
            return filepath;
            
            
          }
          

        }
        return "";
        
        
  
}
return "";
}

void execution(const std::string& input){
  //so basically I will be creating a child process to run the executable and thus use fork to create the child process first

  pid_t pid = fork(); //fork gives an integer where positive number is parent's process 
  //tokenizing the input string 
  std::string word ="";
  std::vector<std::string> words;
  for(int i=0;i<input.length();i++){
    if(input[i]!=' '){
      word+=input[i];
      
    }
    else {
        words.push_back(word);
        word = "";
    }

  }
  if(!word.empty()){
    words.push_back(word);
  }
  std::vector<char*> args;
  for(auto& word:words){
    args.push_back(word.data()); //using .data() instead of &word[0] due to undefined behaviour of &word[0] 

  }
  args.push_back(NULL);
  if(pid ==0){ //child process when pid =0 
     
    execvp(args[0], args.data());
  }

}


int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  
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

    if (command == "echo" || command == "type" || command == "exit"){
      std::cout<< command+" is a shell builtin"<<std::endl;
    }
    
    else{
      std::string filepath = path_file(command);

      if(filepath !=""){
        std::cout<<command+" is "+filepath<<std::endl;

      }
      else{
        std::cout<< command+": not found" <<std::endl;
      }
    }
  }
  
  else{
    
    std::string executable_or_not= path_file(firstword);
    if(executable_or_not != ""){
      execution(input);
    }
  }

  
}
}
