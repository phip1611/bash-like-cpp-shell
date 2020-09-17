/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Background Processes.

#pragma once

#include <vector>
#include "bg-process-state.class.hpp"

/**
 * All background processes (actually only the actives ones, because old ones should be removed; todo!).
 */
extern std::vector<BgProcessState *> bg_processes;
