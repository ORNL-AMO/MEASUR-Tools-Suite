#pragma once

#include <iostream>

/**
 * Compile-time toggle for SteamModeler debug logging.
 *
 * Set STEAM_MODELER_LOGGING to 1 (or pass -DSTEAM_MODELER_LOGGING=1 at the
 * compiler command line) to enable verbose debug output. Leave at 0 for
 * production/WebAssembly builds — the macro expands to nothing, producing
 * zero overhead and no console output.
 *
 * Usage:
 *   SM_LOG("foo=" << foo << ", bar=" << bar);
 */
#ifndef STEAM_MODELER_LOGGING
#define STEAM_MODELER_LOGGING 0
#endif

#if STEAM_MODELER_LOGGING
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SM_LOG(x) (std::cout << x << std::endl)
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SM_LOG(x) do {} while (0)
#endif
