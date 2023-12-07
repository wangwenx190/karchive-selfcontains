#ifndef KARCHIVE_EXPORT_H
#define KARCHIVE_EXPORT_H

#include <QtCore/qcompilerdetection.h>

#ifndef KARCHIVE_EXPORT
#  ifdef KARCHIVE_BUILD_STATIC
#    define KARCHIVE_EXPORT
#  else
#    ifdef KARCHIVE_BUILD_LIBRARY
#      define KARCHIVE_EXPORT Q_DECL_EXPORT
#    else
#      define KARCHIVE_EXPORT Q_DECL_IMPORT
#    endif
#  endif
#endif

#endif // KARCHIVE_EXPORT_H
