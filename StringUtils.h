#ifndef StringUtils_h
#define StringUtils_h

#include <WString.h>
#include "Vector.h"

namespace StringUtils {
  void split (String inputString, Vector<String> &parts, char delimeter = ' ');
}

#endif
