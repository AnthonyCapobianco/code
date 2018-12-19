#pragma once

#include <string>
#include <iostream>

namespace vt::web {
static constexpr bool link = true;

static inline void style(bool is_link = false, const std::string& css = "")
noexcept(true) {
  if (is_link) {
    std::cout << "<style>" << css << "</style>";
  } else {
    std::cout << "<link rel=\"stylesheet\" href=\"" << css << "\">";
  }
}

struct html {
public:
  std::string m_charset;
  std::string m_css;
  std::string m_js;
  std::string m_icon;
  const std::string m_title;
  
  html(const std::string& charset = "UTF-8"
  , const std::string& css = ""
  , const std::string& js = ""
  , const std::string& icon = ""
  , const std::string& title = "no title"
  ) : m_charset(charset), m_css(css), m_js(js), m_icon(icon), m_title(title)  
  noexcept(true) {
    std::cout << "<!DOCTYPE html>" << "<html>" << "<head>"
              << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
              << "<meta charset=\"" + charset + "\">"
              << "<link rel=\"icon\" href=\"" + icon + "\" type=\"image/x-icon\">"
              << "<link rel=\"stylesheet\" href=\"" + css + "\">"
              << "<script src=\"" + js + "\"></script>"
              << "<title>" + title + "</title>"
              << "</head>" << "<body>";
  }
  
  ~html()
  noexcept(true) {
    std::cout << "</body>" << "</html>" << std::endl;
  }
};

struct p {
public:
  p(const std::string& html_class = "") 
  noexcept(false) {
    if (html_class != "") {
      std::cout << "<p class=\"" << html_class << "\">";
    } else {
      std::cout << "<p>";
    }
  }
  
  ~p()
  noexcept(true) {
    std::cout << "</p>" << std::endl;
  }
  
  p& operator<<(const std::string& text) 
  noexcept(false) {
    std::cout << text;
    return *this;
  }
};

} // namespace vt::web