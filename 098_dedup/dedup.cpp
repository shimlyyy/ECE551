#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
size_t hash_helper(std::ifstream & input) {
  std::string line;
  std::string content;
  std::hash<std::string> str_hash;
  while (!input.eof()) {
    getline(input, line);
    content.append(line);
  }
  return str_hash(content);
}

void file_compare_delete_script_helper(std::pair<size_t, std::string> & curr_pair,
                                       std::unordered_map<size_t, std::string> & hashmap) {
  std::unordered_map<size_t, std::string>::iterator it = hashmap.find(curr_pair.first);
  if (it == hashmap.end()) {
    hashmap.insert(curr_pair);
  }
  else {
    std::cout << "#Removing " << curr_pair.second << " (duplicate of " << it->second << ")."
              << std::endl;
    std::cout << "rm " << curr_pair.second << std::endl;
  }
}

void dir_recursion(const std::string & dir, std::unordered_map<size_t, std::string> & myhashmap) {
  DIR * current = opendir(dir.c_str());
  struct dirent * ent = NULL;
  if (current == NULL) {
    std::cerr << "Could not open directory\n";
    exit(EXIT_FAILURE);
  }
  else {
    while ((ent = readdir(current)) != NULL) {
      std::string file_name(ent->d_name);
      if (file_name == "." || file_name == "..") {
        continue;
      }
      else if (ent->d_type == DT_DIR) {
        std::string next_dir = dir + "/" + file_name;
        dir_recursion(next_dir, myhashmap);
      }
      else if (ent->d_type == DT_REG) {
        std::string file = dir + "/" + file_name;
        std::ifstream input(file.c_str());
        if (input.good()) {
          size_t curr_hash;
          curr_hash = hash_helper(input);
          std::pair<size_t, std::string> curr_pair(curr_hash, file);
          file_compare_delete_script_helper(curr_pair, myhashmap);
        }
        else {
          std::cout << "Can not open the file!" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      else {
        std::cerr << "Unknown file type. " << file_name << " will be omitted." << std::endl;
      }
    }
  }
  closedir(current);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    perror("Usage: ./dir (the directory to be dedup-ed). Please re-run the program!");
    return EXIT_FAILURE;
  }
  std::unordered_map<size_t, std::string> hash_map;
  std::cout << "#!/bin/bash" << std::endl;
  for (int i = 1; i < argc; i++) {
    const std::string dir = argv[i];
    dir_recursion(dir, hash_map);
  }
  return EXIT_SUCCESS;
}
