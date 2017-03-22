#pragma once

#define OFXIMGUIPARAM_DELIMITER "||"
#define OFXIMGUIPARAM_STRING_MAX_LENGTH 1256

#define OFXIMGUIPARAM_VERBOSE ofLogVerbose(string(__func__))
#define OFXIMGUIPARAM_NOTICE ofLogNotice(string(__func__))
#define OFXIMGUIPARAM_WARNING ofLogWarning(string(__func__))
#define OFXIMGUIPARAM_ERROR ofLogError(string(__func__))
#define OFXIMGUIPARAM_FATAL ofLogFatalError(string(__func__))
