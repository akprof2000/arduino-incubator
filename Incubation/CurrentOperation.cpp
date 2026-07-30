//
//
//

#include "CurrentOperation.h"

#include "StatusInfo.h"

void CurrentOperationClass::buildText(TextBuilder &builder) { StatusInfo.Print(builder); }
