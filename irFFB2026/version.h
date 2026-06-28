#ifndef IRFFB_VERSION_H
#define IRFFB_VERSION_H

/* ---------------------------------------------------------------------------
 * Single source of truth for the irFFB2026 version.
 * Update these fields together when cutting a release. Consumed by:
 *   - irFFB.rc       (FILEVERSION / PRODUCTVERSION and the version strings)
 *   - irFFB2026.cpp  (the About dialog)
 * ------------------------------------------------------------------------- */

#define IRFFB_VER_MAJOR 1
#define IRFFB_VER_MINOR 3
#define IRFFB_VER_PATCH 0
#define IRFFB_VER_BUILD 0

/* Comma-separated form for the .rc FILEVERSION / PRODUCTVERSION fields. */
#define IRFFB_VER_FILEVERSION IRFFB_VER_MAJOR,IRFFB_VER_MINOR,IRFFB_VER_PATCH,IRFFB_VER_BUILD

/* String forms (keep in sync with the numeric fields above). */
#define IRFFB_VERSION_STR   "1.3.0"
#define IRFFB_VERSION_WSTR  L"1.3.0"

#endif /* IRFFB_VERSION_H */
