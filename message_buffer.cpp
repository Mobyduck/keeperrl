#include "stdafx.h"

#include "message_buffer.h"

template <class Archive> 
void MessageBuffer::serialize(Archive& ar, const unsigned int version) { 
  ar & SVAR(messages);
  CHECK_SERIAL;
}

SERIALIZABLE(MessageBuffer);

MessageBuffer messageBuffer;

void correct(string& msg) {
  if (islower(msg[0]))
    msg[0] = toupper(msg[0]);
  if (msg.size() > 1 && msg[0] == '\"' && islower(msg[1]))
    msg[1] = toupper(msg[1]);
  if (msg.back() != '.' && msg.back() != '?' && msg.back() != '!' && msg.back() != '\"')
    msg.append(".");
}

void MessageBuffer::addMessage(string msg) {
  Debug() << "MSG " << msg;
  CHECK(view != nullptr) << "Message buffer not initialized.";
  if (msg == "")
    return;
  bool imp = isImportant(msg);
  if (imp)
    removeImportant(msg);
  correct(msg);
  if (imp)
    view->addImportantMessage(msg);
  else {
    view->addMessage(msg);
  }
  messages.push_back(msg);
}

void MessageBuffer::addImportantMessage(string msg) {
  addMessage(important(msg));
}

void MessageBuffer::initialize(View* view) {
  this->view = view;
  messages.clear();
}

void MessageBuffer::showHistory() {
  view->presentList("Messages:", View::getListElem(messages), true); 
}

const static string importantPref = "IMPORTANT";

string MessageBuffer::important(const string& msg) {
  return importantPref + msg;
}

bool MessageBuffer::isImportant(const string& msg) {
  return msg.size() > importantPref.size() && msg.substr(0, importantPref.size()) == importantPref;
}

void MessageBuffer::removeImportant(string& msg) {
  CHECK(isImportant(msg));
  msg = msg.substr(importantPref.size());
}
