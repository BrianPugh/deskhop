# Fix Plan: Vertical Monitor Drag Fix Integration

## Summary

Brian's upstream fix (commit `0f73f2a`) adds `.buttons = state->mouse_buttons` to the relative mouse report in `switch_virtual_desktop_macos()` to preserve button state during drag operations across screen boundaries. This fix was **not applied** to the corresponding vertical function `switch_vertical_screen_macos()`, causing buggy drag behavior in vertical layouts.

## The Upstream Fix

```c
// In switch_virtual_desktop_macos() - FIXED by Brian
mouse_report_t move_relative_one = {
    .x = move,
    .mode = RELATIVE,
    .buttons = state->mouse_buttons,  // <-- This line was added
};
```

## The Problem

The vertical equivalent `switch_vertical_screen_macos()` is missing this fix:

```c
// In switch_vertical_screen_macos() - MISSING the fix
mouse_report_t move_relative_one = {
    .y = move,
    .mode = RELATIVE,
    // .buttons is NOT set - defaults to 0, releasing any held buttons!
};
```

When dragging (mouse button held) across vertical screen boundaries on macOS:
1. The edge_position report correctly includes `.buttons = state->mouse_buttons`
2. But the relative nudge reports have `.buttons = 0` (implicit default)
3. This causes the OS to see the button being released during the transition
4. Result: drag operation is interrupted/dropped

## Additional Issue Found

There's also an inconsistency in how horizontal movement is handled in vertical layouts regarding mouse button state:

```c
// In do_screen_switch() for vertical layouts, horizontal movement:
if (output->pos != direction && output->screen_index == output->border_monitor_index) {
    if (state->mouse_buttons)
        return;  // Blocks switching if mouse button held
    switch_to_another_pc(state, output, 1 - state->active_output, direction);
}
```

This blocks computer switching when dragging, which is intentional for the computer border. But for vertical screen transitions (between monitors on the same computer), dragging should be allowed - the original horizontal implementation allows it via `switch_virtual_desktop()`.

## Fix

### Fix 1: Add buttons to vertical macOS relative reports (Required)

In `switch_vertical_screen_macos()`, add `.buttons = state->mouse_buttons`:

```c
mouse_report_t move_relative_one = {
    .y = move,
    .mode = RELATIVE,
    .buttons = state->mouse_buttons,  // ADD THIS LINE
};
```

### Fix 2: Consider drag behavior consistency (Optional)

The horizontal screen switching (`switch_virtual_desktop`) allows dragging between screens 1↔2↔3 on the same computer. The vertical implementation should behave the same way - currently it does, since the mouse_buttons check only applies to computer border switching, not screen transitions.

## Files to Modify

- `src/mouse.c`: Line ~344, add `.buttons = state->mouse_buttons` to `move_relative_one` struct in `switch_vertical_screen_macos()`

## Testing

After fix, verify:
1. Click-drag a window from monitor 1 to monitor 2 in vertical layout on macOS
2. The window should follow the cursor across the boundary without dropping
3. Releasing the mouse button on monitor 2 should complete the drag normally
