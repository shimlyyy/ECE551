#include <dirent.h>
#include <sys/types.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
size_t hash_helper(std::ifstream & input, std::string & path) {
  std::string line;
  size_t value;
  std::string content;
  std::hash<std::string> hash;
  while (input) {
    getline(input, line);
    content.append(line);
  }
  value = hash(content);
  return value;
}

void fileCompare(std::pair<size_t, std::string> & curr_pair,
                 std::unordered_map<size_t, std::string> & hash_map) {
  std::unordered_map<size_t, std::string>::iterator it = hash_map.find(curr_pair.first);
  if (it == hash_map.end()) {
    hash_map.insert(curr_pair);
  }
  else {
    std::cout << "#Removing " << curr_pair.second << " (duplicate of " << it->second << ")."
              << std::endl;
    std::cout << "rm " << curr_pair.second << std::endl;
  }
}
void dir_recursion(std::string & dir, std::unordered_map<size_t, std::string> & hash_map) {
  DIR * current = opendir(dir.c_str());
  struct dirent * ent = NULL;
  if (current == NULL) {
    std::cerr << "can not open directory\n";
    exit(EXIT_FAILURE);
  }
  while ((ent = readdir(current)) != NULL) {
    std::string newfile(ent->d_name);
    if (newfile == "." || newfile == "..") {  //fiter the hidden '.' and '..' file
      continue;
    }
    else if (ent->d_type == DT_DIR) {
      std::string newd = dir + "/" + newfile;
      dir_recursion(newd, hash_map);
    }
    else if (ent->d_type == DT_REG) {
      std::string newd = dir + "/" + newfile;
      std::ifstream input(newd.c_str());
      if (input.good()) {
        size_t curr_hash = hash_helper(input, newd);
        std::pair<size_t, std::string> curr_pair(curr_hash, newd);
        fileCompare(curr_pair, hash_map);
      }
      else {
        std::cout << "can not open file\n";
        exit(EXIT_FAILURE);
      }
    }
  }
  closedir(current);
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    std::cerr << " no directory\n";
    return EXIT_FAILURE;
  }
  std::unordered_map<size_t, std::string> hash_map;
  std::cout << "#!/bin/bash"
            << "\n";
  for (int i = 1; i < argc; i++) {
    std::string dir(argv[i]);
    dir_recursion(dir, hash_map);
  }
  return EXIT_SUCCESS;
}
