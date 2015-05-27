#include "./shader.h"

namespace yengine { namespace gfx {
  Shader::Shader(const char* vertPath, const char* fragPath)
      : m_VertPath(vertPath), m_FragPath(fragPath)
  {
    m_ShaderId = load();
  }

  Shader::~Shader()
  {
    glDeleteProgram(m_ShaderId);
  }

  GLuint Shader::load()
  {
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLint result;

    std::string vertSourceStr = FileInput::read_file(m_VertPath);
    std::string fragSourceStr = FileInput::read_file(m_FragPath);

    const char* vertSource = vertSourceStr.c_str();
    const char* fragSource = fragSourceStr.c_str();

    glShaderSource(vertex, 1, &vertSource, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

    // in case the shader failed
    if (result == GL_FALSE) {
      GLint length;
      glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> error(length);
      glGetShaderInfoLog(vertex, length, &length, &error[0]);
      std::cout << "Failed to compile vshader: " << std::endl
                << &error[0] << std::endl;
      glDeleteShader(vertex);

      return 0;
    }

    glShaderSource(fragment, 1, &fragSource, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

    // in case the shader failed
    if (result == GL_FALSE) {
      GLint length;
      glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> error(length);
      glGetShaderInfoLog(fragment, length, &length, &error[0]);
      std::cout << "Failed to compile vshader: " << std::endl
                << &error[0] << std::endl;
      glDeleteShader(fragment);

      return 0;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
  }

  void Shader::enable () const
  {
    glUseProgram(m_ShaderId);
  }

  void Shader::disable () const
  {
    glUseProgram(0);
  }

  GLint Shader::getUniformLocation(const GLchar* name)
  {
    return glGetUniformLocation(m_ShaderId, name);
  }

  void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
  {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(matrix));
  }

  void Shader::setUniform4f(const GLchar* name, const glm::vec4& vec)
  {
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(vec));
  }

  void Shader::setUniform2f(const GLchar* name, const glm::vec2& vec)
  {
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(vec));
  }

  void Shader::setUniform1i(const GLchar* name, const int value)
  {
    glUniform1i(getUniformLocation(name), value);
  }


}};

