/*
 * This file is part of DeskHop (https://github.com/hrvach/deskhop).
 * Copyright (c) 2025 Hrvoje Cavrak
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * See the file LICENSE for the full license text.
 */
#pragma once

#include <stdint.h>


/*==============================================================================
 *  Constants
 *==============================================================================*/

#define MAX_SCREEN_COORD 32767
#define MIN_SCREEN_COORD 0
#define MAX_SCREEN_COUNT 3  // Max physical monitors per computer

/*==============================================================================
 *  Data Structures
 *==============================================================================*/

typedef struct {
    int16_t start;
    int16_t end;
} border_size_t;

typedef struct {
    border_size_t from;
    border_size_t to;
} horizontal_transition_t;

typedef horizontal_transition_t vertical_transition_t;

typedef enum {
    MONITOR_LAYOUT_HORIZONTAL = 0,
    MONITOR_LAYOUT_VERTICAL = 1
} monitor_layout_t;

typedef struct {
    uint8_t mode;
    uint8_t only_if_inactive;
    uint64_t idle_time_us;
    uint64_t max_time_us;
} screensaver_t;

typedef struct {
    uint32_t number;
    uint32_t screen_count;
    uint32_t screen_index;
    int32_t speed_x;
    int32_t speed_y;
    horizontal_transition_t horizontal_transition[MAX_SCREEN_COUNT - 1];
    vertical_transition_t vertical_transition[MAX_SCREEN_COUNT - 1];
    uint8_t os;
    uint8_t pos;
    uint8_t mouse_park_pos;
    monitor_layout_t monitor_layout;
    uint8_t border_monitor_index;
    screensaver_t screensaver;
} output_t;
