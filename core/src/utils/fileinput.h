#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <string.h>
#include <fstream>

namespace yengine {

  class FileInput
  {
  public:
    static std::string read_file(const char* filename)
    {
      unsigned long length;
      char* data;
      FILE* file = fopen(filename, "rt");

      fseek(file, 0, SEEK_END);
      length = ftell(file);
      data = new char[length + 1];
      memset(data, 0, length + 1);
      fseek(file, 0, SEEK_SET);
      fread(data, 1, length, file);
      fclose(file);

      std::string result(data);
      delete[] data;

      return result;
    };
  };

} // ns yengine;

#endif
