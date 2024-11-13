#include "CallsignValidator.hpp"

CallsignValidator::CallsignValidator (QObject * parent, bool allow_compound)
  : QValidator {parent}
  , re_ {allow_compound ? 
      R"(^(([A-Z]{2}|\\d[A-Z]|[A-Z]\\d)/)?([A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d+[A-Z]+(/(P|M|A|\\d|QRP|(([A-Z]{2}|\\d[A-Z]|[A-Z]\\d))))$)"
      : R"(^([A-Z]{2}|\\d[A-Z]|[A-Z]\\d)\\d+[A-Z]+$)"}
{
}

auto CallsignValidator::validate (QString& input, int& pos) const -> State
{
  re_.setPatternOptions( QRegularExpression::CaseInsensitiveOption );
  auto match = re_.match (input, 0, QRegularExpression::PartialPreferCompleteMatch);
  input = input.toUpper ();
  if (match.hasMatch ()) return Acceptable;
  if (!input.size () || match.hasPartialMatch ()) return Intermediate;
  pos = input.size ();
  return Invalid;
}
