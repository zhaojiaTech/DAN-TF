// GENERATED FILE - DO NOT MODIFY
#include "tensorflow/core/util/event.pb_text-impl.h"

using ::tensorflow::strings::Scanner;
using ::tensorflow::strings::StrCat;

namespace tensorflow {

string ProtoDebugString(
    const ::tensorflow::Event& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::Event& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::Event& msg) {
  o->AppendNumericIfNotZero("wall_time", msg.wall_time());
  o->AppendNumericIfNotZero("step", msg.step());
  if (msg.what_case() == ::tensorflow::Event::kFileVersion) {
    o->AppendString("file_version", ProtobufStringToString(msg.file_version()));
  }
  if (msg.what_case() == ::tensorflow::Event::kGraphDef) {
    o->AppendString("graph_def", ProtobufStringToString(msg.graph_def()));
  }
  if (msg.what_case() == ::tensorflow::Event::kSummary) {
    o->OpenNestedMessage("summary");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.summary());
    o->CloseNestedMessage();
  }
  if (msg.what_case() == ::tensorflow::Event::kLogMessage) {
    o->OpenNestedMessage("log_message");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.log_message());
    o->CloseNestedMessage();
  }
  if (msg.what_case() == ::tensorflow::Event::kSessionLog) {
    o->OpenNestedMessage("session_log");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.session_log());
    o->CloseNestedMessage();
  }
  if (msg.what_case() == ::tensorflow::Event::kTaggedRunMetadata) {
    o->OpenNestedMessage("tagged_run_metadata");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.tagged_run_metadata());
    o->CloseNestedMessage();
  }
  if (msg.what_case() == ::tensorflow::Event::kMetaGraphDef) {
    o->AppendString("meta_graph_def", ProtobufStringToString(msg.meta_graph_def()));
  }
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::Event* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::Event* msg) {
  std::vector<bool> has_seen(9, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "wall_time") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      double value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_wall_time(value);
    }
    else if (identifier == "step") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      int64 value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseNumericFromScanner(scanner, &value)) return false;
      msg->set_step(value);
    }
    else if (identifier == "file_version") {
      if (msg->what_case() != 0) return false;
      if (has_seen[2]) return false;
      has_seen[2] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_file_version());
    }
    else if (identifier == "graph_def") {
      if (msg->what_case() != 0) return false;
      if (has_seen[3]) return false;
      has_seen[3] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_graph_def());
    }
    else if (identifier == "summary") {
      if (msg->what_case() != 0) return false;
      if (has_seen[4]) return false;
      has_seen[4] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_summary())) return false;
    }
    else if (identifier == "log_message") {
      if (msg->what_case() != 0) return false;
      if (has_seen[5]) return false;
      has_seen[5] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_log_message())) return false;
    }
    else if (identifier == "session_log") {
      if (msg->what_case() != 0) return false;
      if (has_seen[6]) return false;
      has_seen[6] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_session_log())) return false;
    }
    else if (identifier == "tagged_run_metadata") {
      if (msg->what_case() != 0) return false;
      if (has_seen[7]) return false;
      has_seen[7] = true;
      const char open_char = scanner->Peek();
      if (open_char != '{' && open_char != '<') return false;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      if (!::tensorflow::internal::ProtoParseFromScanner(
          scanner, true, open_char == '{', msg->mutable_tagged_run_metadata())) return false;
    }
    else if (identifier == "meta_graph_def") {
      if (msg->what_case() != 0) return false;
      if (has_seen[8]) return false;
      has_seen[8] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_meta_graph_def());
    }
  }
}

}  // namespace internal

const char* EnumName_LogMessage_Level(
    ::tensorflow::LogMessage_Level value) {
  switch (value) {
    case 0: return "UNKNOWN";
    case 10: return "DEBUGGING";
    case 20: return "INFO";
    case 30: return "WARN";
    case 40: return "ERROR";
    case 50: return "FATAL";
    default: return "";
  }
}

string ProtoDebugString(
    const ::tensorflow::LogMessage& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::LogMessage& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::LogMessage& msg) {
  if (msg.level() != 0) {
    o->AppendEnumName("level", ::tensorflow::EnumName_LogMessage_Level(msg.level()));
  }
  o->AppendStringIfNotEmpty("message", ProtobufStringToString(msg.message()));
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::LogMessage* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::LogMessage* msg) {
  std::vector<bool> has_seen(2, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "level") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "UNKNOWN" || value == "0" || value == "-0") {
        msg->set_level(::tensorflow::LogMessage_Level_UNKNOWN);
      } else if (value == "DEBUGGING" || value == "10") {
        msg->set_level(::tensorflow::LogMessage_Level_DEBUGGING);
      } else if (value == "INFO" || value == "20") {
        msg->set_level(::tensorflow::LogMessage_Level_INFO);
      } else if (value == "WARN" || value == "30") {
        msg->set_level(::tensorflow::LogMessage_Level_WARN);
      } else if (value == "ERROR" || value == "40") {
        msg->set_level(::tensorflow::LogMessage_Level_ERROR);
      } else if (value == "FATAL" || value == "50") {
        msg->set_level(::tensorflow::LogMessage_Level_FATAL);
      } else {
        return false;
      }
    }
    else if (identifier == "message") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_message());
    }
  }
}

}  // namespace internal

const char* EnumName_SessionLog_SessionStatus(
    ::tensorflow::SessionLog_SessionStatus value) {
  switch (value) {
    case 0: return "STATUS_UNSPECIFIED";
    case 1: return "START";
    case 2: return "STOP";
    case 3: return "CHECKPOINT";
    default: return "";
  }
}

string ProtoDebugString(
    const ::tensorflow::SessionLog& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::SessionLog& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::SessionLog& msg) {
  if (msg.status() != 0) {
    o->AppendEnumName("status", ::tensorflow::EnumName_SessionLog_SessionStatus(msg.status()));
  }
  o->AppendStringIfNotEmpty("checkpoint_path", ProtobufStringToString(msg.checkpoint_path()));
  o->AppendStringIfNotEmpty("msg", ProtobufStringToString(msg.msg()));
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::SessionLog* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::SessionLog* msg) {
  std::vector<bool> has_seen(3, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "status") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      StringPiece value;
      if (!parsed_colon || !scanner->RestartCapture().Many(Scanner::LETTER_DIGIT_DASH_UNDERSCORE).GetResult(nullptr, &value)) return false;
      if (value == "STATUS_UNSPECIFIED" || value == "0" || value == "-0") {
        msg->set_status(::tensorflow::SessionLog_SessionStatus_STATUS_UNSPECIFIED);
      } else if (value == "START" || value == "1") {
        msg->set_status(::tensorflow::SessionLog_SessionStatus_START);
      } else if (value == "STOP" || value == "2") {
        msg->set_status(::tensorflow::SessionLog_SessionStatus_STOP);
      } else if (value == "CHECKPOINT" || value == "3") {
        msg->set_status(::tensorflow::SessionLog_SessionStatus_CHECKPOINT);
      } else {
        return false;
      }
    }
    else if (identifier == "checkpoint_path") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_checkpoint_path());
    }
    else if (identifier == "msg") {
      if (has_seen[2]) return false;
      has_seen[2] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_msg());
    }
  }
}

}  // namespace internal

string ProtoDebugString(
    const ::tensorflow::TaggedRunMetadata& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::TaggedRunMetadata& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::TaggedRunMetadata& msg) {
  o->AppendStringIfNotEmpty("tag", ProtobufStringToString(msg.tag()));
  o->AppendStringIfNotEmpty("run_metadata", ProtobufStringToString(msg.run_metadata()));
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::TaggedRunMetadata* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::TaggedRunMetadata* msg) {
  std::vector<bool> has_seen(2, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "tag") {
      if (has_seen[0]) return false;
      has_seen[0] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_tag());
    }
    else if (identifier == "run_metadata") {
      if (has_seen[1]) return false;
      has_seen[1] = true;
      string str_value;
      if (!parsed_colon || !::tensorflow::strings::ProtoParseStringLiteralFromScanner(
          scanner, &str_value)) return false;
      SetProtobufStringSwapAllowed(&str_value, msg->mutable_run_metadata());
    }
  }
}

}  // namespace internal

string ProtoDebugString(
    const ::tensorflow::SessionStatus& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, false);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

string ProtoShortDebugString(
    const ::tensorflow::SessionStatus& msg) {
  string s;
  ::tensorflow::strings::ProtoTextOutput o(&s, true);
  internal::AppendProtoDebugString(&o, msg);
  o.CloseTopMessage();
  return s;
}

namespace internal {

void AppendProtoDebugString(
    ::tensorflow::strings::ProtoTextOutput* o,
    const ::tensorflow::SessionStatus& msg) {
  for (int i = 0; i < msg.event_size(); ++i) {
    o->OpenNestedMessage("event");
    ::tensorflow::internal::AppendProtoDebugString(o, msg.event(i));
    o->CloseNestedMessage();
  }
}

}  // namespace internal

bool ProtoParseFromString(
    const string& s,
    ::tensorflow::SessionStatus* msg) {
  msg->Clear();
  Scanner scanner(s);
  if (!internal::ProtoParseFromScanner(&scanner, false, false, msg)) return false;
  scanner.Eos();
  return scanner.GetResult();
}

namespace internal {

bool ProtoParseFromScanner(
    ::tensorflow::strings::Scanner* scanner, bool nested, bool close_curly,
    ::tensorflow::SessionStatus* msg) {
  std::vector<bool> has_seen(1, false);
  while(true) {
    ProtoSpaceAndComments(scanner);
    if (nested && (scanner->Peek() == (close_curly ? '}' : '>'))) {
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
      return true;
    }
    if (!nested && scanner->empty()) { return true; }
    scanner->RestartCapture()
        .Many(Scanner::LETTER_DIGIT_UNDERSCORE)
        .StopCapture();
    StringPiece identifier;
    if (!scanner->GetResult(nullptr, &identifier)) return false;
    bool parsed_colon = false;
    (void)parsed_colon;
    ProtoSpaceAndComments(scanner);
    if (scanner->Peek() == ':') {
      parsed_colon = true;
      scanner->One(Scanner::ALL);
      ProtoSpaceAndComments(scanner);
    }
    if (identifier == "event") {
      const bool is_list = (scanner->Peek() == '[');
      do {
        if (is_list) {
          scanner->One(Scanner::ALL);
          ProtoSpaceAndComments(scanner);
        }
        const char open_char = scanner->Peek();
        if (open_char != '{' && open_char != '<') return false;
        scanner->One(Scanner::ALL);
        ProtoSpaceAndComments(scanner);
        if (!::tensorflow::internal::ProtoParseFromScanner(
            scanner, true, open_char == '{', msg->add_event())) return false;
      } while (is_list && scanner->Peek() == ',');
      if (is_list && !scanner->OneLiteral("]").GetResult()) return false;
    }
  }
}

}  // namespace internal

}  // namespace tensorflow
