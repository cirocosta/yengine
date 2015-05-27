#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <FreeImage.h>
#include <GL/glew.h>
#include <string.h>
#include <fstream>

namespace yengine {

  class FileInput
  {
  public:
    static std::string read_file(const char* filename)
    {
      // TODO include file presence checking
      // with fstat. Would also be great to not
      // rely on fread, but a more secure one.
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

    static BYTE* read_image(const char* filename, GLsizei* width,
                            GLsizei* height)
    {
      FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
      FIBITMAP *dib = nullptr;

      fif = FreeImage_GetFileType(filename, 0);
      if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
      if (fif == FIF_UNKNOWN)
        return nullptr;

      if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
      if (!dib)
        return nullptr;

      BYTE* result = FreeImage_GetBits(dib);
      *width = FreeImage_GetWidth(dib);
      *height = FreeImage_GetHeight(dib);

      return result;
    }
  };

} // ns yengine;

#endif
