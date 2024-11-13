#include "CallsignValidator.hpp"

CallsignValidator::CallsignValidator (QObject * parent, bool allow_compound)
  : QValidator {parent}
  , re_ {allow_compound ? 
      R"(^(([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d?/)?([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d+[A-Z]+(/(P|M|A|\\d|QRP|(([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d?)))?$)"
      : R"(^([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d+[A-Z]+$)"}
  , _pattern {
    allow_compound ? 
      "^(([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d?/)?([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d+[A-Z]+(/(P|M|A|\\d|QRP|(([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d?)))?$"
      : "^([BFGIKMNRUWDS]|[A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d+[A-Z]+$"
  }
{
}

auto CallsignValidator::validate (QString& input, int& pos) const -> State
{
  QRegularExpression reCall = QRegularExpression( _pattern, QRegularExpression::CaseInsensitiveOption );
  // re_.setPatternOptions( QRegularExpression::CaseInsensitiveOption );
  auto match = reCall.match (input, 0, QRegularExpression::PartialPreferCompleteMatch);
  input = input.toUpper ();
  if (match.hasMatch ()) return Acceptable;
  if (!input.size () || match.hasPartialMatch ()) return Intermediate;
  pos = input.size ();
  return Invalid;
}
