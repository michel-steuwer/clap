#pragma once

#include  <stack>
#include  <string>
#include  <sstream>

namespace clap {

/// @namespace xml Contains the XML formatting class and utility functions
namespace xml {

/// @class ostream XML output stream formatter.
class ostream {
public:
  /// @brief Build an XML stream from an output stream
  inline ostream(std::ostream& s) : s(s) {}

  /// @brief Destructor. All tags are automatically closed
  ~ostream() { while (tags.size()) endTag(tags.top()); }

  /// @brief If the operator is not overloaded, the default behavior
  ///   sends it to the output stream
  /// @tparam T Any type for which the operator<< is not overloaded
  /// @param value Object to print
  template<class T>
  ostream& operator<<(const T& value) {
    s << value;
    return *this;
  }

  /// @cond HIDDEN_SYMBOLS
  /// implementation details
  
  /// Controller for the XML stream
  struct Controller {
    /// @brief The different types of actions supported
    enum class Action {
      Tag,       /// < Open new tag
      TagEnd,    /// < Close current tag
      Attribute  /// < Open new attribute
    } action;

    /// @brief Payload
    std::string str;

    /// @brief Create an action
    inline Controller(const Action S) : action{S} {}
    /// @brief Create an action with a payload
    inline Controller(const Action S, const std::string& str) : action{S}, str{str} {}
    /// @brief Copy a Controller object
    inline Controller(const Controller& c) = default;
  };

  ostream& operator<<(const Controller& controller) {
    switch (controller.action) {
    case Controller::Action::Tag:
      closeTagStart();
      s << pad << '<'<< controller.str;
      tags.push(controller.str);
      state = State::Tag;
      pad.resize(2*tags.size(), ' ');
      break; 

    case Controller::Action::TagEnd:
      endTag(controller.str);
      break; 

    case Controller::Action::Attribute:
      if(State::Attr == state)
        s << '\"';

      if (State::None != state) {
        s << ' ' << controller.str << "=\"";
        state = State::Attr;
      }
      break;  

    default: break;
    }
    return  *this;
  }

private:
  std::string pad;

  enum class State {None, Tag, Attr} state = State::None;

  std::stack<std::string> tags;

  std::ostream& s;

  void closeTagStart(bool self_closed = false) {
    switch (state) {
    case State::Attr: s << '\"';
    case State::Tag:
      if (self_closed) s << '/';
      s << ">\n";
    default: break;
    }
  }

  void endTag(const std::string& tag) {
    bool brk = false;

    while (tags.size() > 0 && !brk) {
      if (State::None == state) {
        pad.resize(2*(tags.size()-1), ' ');
        s << pad << "</" << tags.top() << '>' << '\n';
      }
      else {
        closeTagStart(true);
        state = State::None;
      }
      brk = tag.empty() || tag == tags.top();
      tags.pop();
      pad.resize(2*tags.size(), ' ');
    }
  }

  /// @endcond
};  

/// @brief Open a new tag
inline const ostream::Controller tag(const std::string& tag_name) 
{ return {ostream::Controller::Action::Tag, tag_name}; }

/// @brief Close the current tag
inline const ostream::Controller endtag() 
{ return {ostream::Controller::Action::TagEnd}; }

/// @brief Close a specific tag
inline const ostream::Controller endtag(const std::string& tag_name) 
{ return {ostream::Controller::Action::TagEnd, tag_name}; }

/// @brief Open a new attribute
inline const ostream::Controller attr(const std::string& attr_name) 
{ return {ostream::Controller::Action::Attribute, attr_name}; }

}
}

