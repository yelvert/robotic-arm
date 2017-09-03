#include <WString.h>
#include "Vector.h"
#include "StringUtils.h"

void StringUtils::split (String inputString, Vector<String> &parts, char delimeter = ' ') {
  parts.clear();
  for (int i = 0, j = 0 ; i < inputString.length() ; i++ ) {
    if (i == inputString.length()-1) {
      if (inputString[i] == delimeter) {
        if (j!= i) {
          parts.push_back(inputString.substring(j, i));
        }
      } else {
        parts.push_back(inputString.substring(j));
      }
      continue;
    }
    if (inputString[i] == delimeter) {
      if (j != i) {
        parts.push_back(inputString.substring(j, i));
      }
      j = i+1;
    }
  }
}
