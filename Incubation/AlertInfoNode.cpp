//
//
//

#include "AlertInfoNode.h"

#include "Alerting.h"

void AlertInfoNodeClass::buildText(TextBuilder &builder) { Alerting.Print(builder); }
