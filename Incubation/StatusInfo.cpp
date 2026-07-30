//
//
//

#include "StatusInfo.h"

StatusInfoClass StatusInfo;

void StatusInfoClass::AddStatus(StatusOper status, double fill) {
  if (status >= so_count) return;

  long percent = lround(fill * 100.0 / 255.0);
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  _oper[status] = static_cast<uint8_t>(percent);

  // Одновременно выдувать и проветривать бессмысленно: проветривание главнее.
  if (_oper[so_blow] != 0) _oper[so_cool] = 0;
}

void StatusInfoClass::Print(TextBuilder &builder) const {
  for (uint8_t i = 0; i < so_count; i++) {
    if (_oper[i] == 0) continue;

    builder.addSeparator();
    builder.addP(Txt::OperFirst + i);

    // У «процентных» операций после названия открыта скобка — закрываем её
    // значением. У событийных (поворот, дверь, ...) скобки нет.
    switch (static_cast<StatusOper>(i)) {
      case so_none:
      case so_heet:
      case so_cool:
      case so_wet:
      case so_dry:
        builder.add(static_cast<unsigned int>(_oper[i]));
        builder.addP(Txt::PctClose);
        break;
      default:
        break;
    }
  }

  if (builder.empty()) builder.addP(Txt::NoActions);
}
