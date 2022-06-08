#include "opengbex.h"

int lastErrorCode = OPENGB_NO_ERROR;

int opengb_GetLastOpenGBErrorCode() {
    return lastErrorCode;
}

void opengb_SetLastOpenGBErrorCode(int errorCode) {
    lastErrorCode = errorCode;
}