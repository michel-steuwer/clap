#pragma once

#include  <stack>
#include  <string>
#include  <sstream>

namespace He {
namespace xml {
class ostream {
public:
  struct Controller {
    enum class Action {Tag, TagEnd, Attribute, CharData, NoOp};
    Action action;
    std::string str;

    inline Controller(const Action S) : action{S} {}
    inline Controller(const Action S, const std::string& str) : action{S}, str{str} {}
    inline Controller(const Controller& c) = default;
  };

  inline ostream(std::ostream& s) : s(s) {}

  ~ostream() { while (tags.size()) endTag(tags.top()); }

  template<class T>
  ostream& operator<<(const T& value) {
    s << value;
    return *this;
  }

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

    case Controller::Action::CharData:
      closeTagStart();
      state = State::None;
      break; 
    default: break;
    }
    return  *this;
  }

private:
  std::string pad;

  enum class State {None, Tag, Attr};
  State state = State::None;

  std::stack<std::string>  tags;
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
};  

inline const ostream::Controller tag(const std::string& tag_name) {
  return {ostream::Controller::Action::Tag, tag_name};
}

inline const ostream::Controller endtag() {
  return {ostream::Controller::Action::TagEnd};
}

inline const ostream::Controller endtag(const std::string& tag_name) {
  return {ostream::Controller::Action::TagEnd, tag_name};
}

inline const ostream::Controller attr(const std::string& attr_name) {
  return {ostream::Controller::Action::Attribute, attr_name};
}

inline const ostream::Controller chardata() {
  return {ostream::Controller::Action::CharData};
}

inline const ostream::Controller noOp() {
  return {ostream::Controller::Action::NoOp};
}

}
}

