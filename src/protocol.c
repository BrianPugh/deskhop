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
#include "main.h"

const field_map_t api_field_map[] = {
/* Index, Rdonly, Type, Len, Offset in struct */
    { 0,  true,  UINT8,  1, offsetof(device_t, active_output) },
    { 1,  true,  INT16,  2, offsetof(device_t, pointer_x) },
    { 2,  true,  INT16,  2, offsetof(device_t, pointer_y) },
    { 3,  true,  INT16,  2, offsetof(device_t, mouse_buttons) },

    /* Output A */
    { 10, false, UINT32, 4, offsetof(device_t, config.output[0].number) },
    { 11, false, UINT32, 4, offsetof(device_t, config.output[0].screen_count) },
    { 12, false, INT32,  4, offsetof(device_t, config.output[0].speed_x) },
    { 13, false, INT32,  4, offsetof(device_t, config.output[0].speed_y) },
    { 16, false, UINT8,  1, offsetof(device_t, config.output[0].os) },
    { 17, false, UINT8,  1, offsetof(device_t, config.output[0].pos) },
    { 18, false, UINT8,  1, offsetof(device_t, config.output[0].mouse_park_pos) },
    { 19, false, UINT8,  1, offsetof(device_t, config.output[0].screensaver.mode) },
    { 20, false, UINT8,  1, offsetof(device_t, config.output[0].screensaver.only_if_inactive) },

    /* Until we increase the payload size from 8 bytes, clamp to avoid exceeding the field size */
    { 21, false, UINT64, 7, offsetof(device_t, config.output[0].screensaver.idle_time_us) },
    { 22, false, UINT64, 7, offsetof(device_t, config.output[0].screensaver.max_time_us) },

    /* Output A screen transitions */
    { 23, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[0].from.start) },
    { 24, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[0].from.end) },
    { 25, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[0].to.start) },
    { 26, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[0].to.end) },
    { 27, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[1].from.start) },
    { 28, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[1].from.end) },
    { 29, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[1].to.start) },
    { 30, false, INT16, 2, offsetof(device_t, config.output[0].horizontal_transition[1].to.end) },

    /* Output A vertical transitions */
    { 31, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[0].from.start) },
    { 32, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[0].from.end) },
    { 33, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[0].to.start) },
    { 34, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[0].to.end) },
    { 35, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[1].from.start) },
    { 36, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[1].from.end) },
    { 37, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[1].to.start) },
    { 38, false, INT16, 2, offsetof(device_t, config.output[0].vertical_transition[1].to.end) },

    /* Output A monitor layout */
    { 14, false, UINT8, 1, offsetof(device_t, config.output[0].monitor_layout) },
    { 15, false, UINT8, 1, offsetof(device_t, config.output[0].border_monitor_index) },

    /* Output B */
    { 40, false, UINT32, 4, offsetof(device_t, config.output[1].number) },
    { 41, false, UINT32, 4, offsetof(device_t, config.output[1].screen_count) },
    { 42, false, INT32,  4, offsetof(device_t, config.output[1].speed_x) },
    { 43, false, INT32,  4, offsetof(device_t, config.output[1].speed_y) },
    { 46, false, UINT8,  1, offsetof(device_t, config.output[1].os) },
    { 47, false, UINT8,  1, offsetof(device_t, config.output[1].pos) },
    { 48, false, UINT8,  1, offsetof(device_t, config.output[1].mouse_park_pos) },
    { 49, false, UINT8,  1, offsetof(device_t, config.output[1].screensaver.mode) },
    { 50, false, UINT8,  1, offsetof(device_t, config.output[1].screensaver.only_if_inactive) },
    { 51, false, UINT64, 7, offsetof(device_t, config.output[1].screensaver.idle_time_us) },
    { 52, false, UINT64, 7, offsetof(device_t, config.output[1].screensaver.max_time_us) },

    /* Output B screen transitions */
    { 53, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[0].from.start) },
    { 54, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[0].from.end) },
    { 55, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[0].to.start) },
    { 56, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[0].to.end) },
    { 57, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[1].from.start) },
    { 58, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[1].from.end) },
    { 59, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[1].to.start) },
    { 60, false, INT16, 2, offsetof(device_t, config.output[1].horizontal_transition[1].to.end) },

    /* Output B vertical transitions */
    { 61, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[0].from.start) },
    { 62, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[0].from.end) },
    { 63, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[0].to.start) },
    { 64, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[0].to.end) },
    { 65, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[1].from.start) },
    { 66, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[1].from.end) },
    { 67, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[1].to.start) },
    { 68, false, INT16, 2, offsetof(device_t, config.output[1].vertical_transition[1].to.end) },

    /* Output B monitor layout */
    { 44, false, UINT8, 1, offsetof(device_t, config.output[1].monitor_layout) },
    { 45, false, UINT8, 1, offsetof(device_t, config.output[1].border_monitor_index) },

    /* Common config */
    { 70, false, UINT32, 4, offsetof(device_t, config.version) },
    { 71, false, UINT8,  1, offsetof(device_t, config.force_mouse_boot_mode) },
    { 72, false, UINT8,  1, offsetof(device_t, config.force_kbd_boot_protocol) },
    { 73, false, UINT8,  1, offsetof(device_t, config.kbd_led_as_indicator) },
    { 74, false, UINT8,  1, offsetof(device_t, config.hotkey_toggle) },
    { 75, false, UINT8,  1, offsetof(device_t, config.enable_acceleration) },
    { 76, false, UINT8,  1, offsetof(device_t, config.enforce_ports) },
    { 77, false, UINT16, 2, offsetof(device_t, config.jump_threshold) },

    /* Firmware */
    { 78, true,  UINT16, 2, offsetof(device_t, _running_fw.version) },
    { 79, true,  UINT32, 4, offsetof(device_t, _running_fw.checksum) },

    { 80, true,  UINT8,  1, offsetof(device_t, keyboard_connected) },
    { 81, true,  UINT8,  1, offsetof(device_t, switch_lock) },
    { 82, true,  UINT8,  1, offsetof(device_t, relative_mouse) },

    /* Computer border (A↔B transition) */
    { 83, false, INT16, 2, offsetof(device_t, config.horizontal_computer_border.from.start) },
    { 84, false, INT16, 2, offsetof(device_t, config.horizontal_computer_border.from.end) },
    { 85, false, INT16, 2, offsetof(device_t, config.horizontal_computer_border.to.start) },
    { 86, false, INT16, 2, offsetof(device_t, config.horizontal_computer_border.to.end) },

    /* Hold-to-switch threshold */
    { 87, false, UINT16, 2, offsetof(device_t, config.hold_threshold_ms) },

    /* Vertical computer border */
    { 88, false, INT16, 2, offsetof(device_t, config.vertical_computer_border.from.start) },
    { 89, false, INT16, 2, offsetof(device_t, config.vertical_computer_border.from.end) },
    { 90, false, INT16, 2, offsetof(device_t, config.vertical_computer_border.to.start) },
    { 91, false, INT16, 2, offsetof(device_t, config.vertical_computer_border.to.end) },
};

const field_map_t* get_field_map_entry(uint32_t index) {
    for (unsigned int i = 0; i < ARRAY_SIZE(api_field_map); i++) {
        if (api_field_map[i].idx == index) {
            return &api_field_map[i];
        }
    }

    return NULL;
}


const field_map_t* get_field_map_index(uint32_t index) {
    /* Clamp potential overflows to last element. */
    if (index >= ARRAY_SIZE(api_field_map))
        index = ARRAY_SIZE(api_field_map) - 1;

    return &api_field_map[index];
}

size_t get_field_map_length(void) {
    return ARRAY_SIZE(api_field_map);
}

void _queue_packet(uint8_t *payload, device_t *state, uint8_t type, uint8_t len, uint8_t id, uint8_t inst) {
    hid_generic_pkt_t generic_packet = {
        .instance = inst,
        .report_id = id,
        .type = type,
        .len = len,
    };

    memcpy(generic_packet.data, payload, len);
    queue_try_add(&state->hid_queue_out, &generic_packet);
}

void queue_cfg_packet(uart_packet_t *packet, device_t *state) {
    uint8_t raw_packet[RAW_PACKET_LENGTH];
    write_raw_packet(raw_packet, packet);
    _queue_packet(raw_packet, state, 0, RAW_PACKET_LENGTH, REPORT_ID_VENDOR, ITF_NUM_HID_VENDOR);
}

void queue_cc_packet(uint8_t *payload, device_t *state) {
    _queue_packet(payload, state, 1, CONSUMER_CONTROL_LENGTH, REPORT_ID_CONSUMER, ITF_NUM_HID);
}

void queue_system_packet(uint8_t *payload, device_t *state) {
    _queue_packet(payload, state, 2, SYSTEM_CONTROL_LENGTH, REPORT_ID_SYSTEM, ITF_NUM_HID);
}
