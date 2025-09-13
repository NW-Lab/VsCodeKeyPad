# Keypad Layout Design

```
┌─────────────────────────────────┐
│ VS Code Pad        BLE Connected│  <- Header (40px)
├─────────────────────────────────┤
│ ┌─────────┐ ┌───────────────────┐│
│ │ Accept  │ │  Accept Word      ││  <- Row 1: Copilot Keys (red)
│ │  (Tab)  │ │  (Ctrl+→)         ││
│ └─────────┘ └───────────────────┘│
│ ┌─────────┐ ┌───────────────────┐│
│ │ Reject  │ │  Show Copilot     ││  <- Row 2: More Copilot (red)
│ │ (Esc)   │ │  (Ctrl+Tab)       ││
│ └─────────┘ └───────────────────┘│
│ ┌─────────┐ ┌───────────────────┐│
│ │Quick Open│ │  Command          ││  <- Row 3: VS Code (blue)
│ │(Ctrl+P) │ │  (Ctrl+Shift+P)   ││
│ └─────────┘ └───────────────────┘│
│ ┌─────────┐ ┌───────────────────┐│
│ │Save All │ │  Format           ││  <- Row 4: More VS Code (blue)
│ │(Ctrl+⇧S)│ │  (Shift+Alt+F)    ││
│ └─────────┘ └───────────────────┘│
│ ┌─────────┐ ┌───────────────────┐│
│ │ Debug   │ │  Terminal         ││  <- Row 5: Tools (blue)
│ │  (F5)   │ │  (Ctrl+`)         ││
│ └─────────┘ └───────────────────┘│
│ ┌─────────┐ ┌───────────────────┐│
│ │Settings │ │  Mode Switch      ││  <- Row 6: Config (blue)
│ │(Ctrl+,) │ │  (BLE/USB)        ││
│ └─────────┘ └───────────────────┘│
└─────────────────────────────────┘
```

## Color Scheme:
- **Red Keys**: GitHub Copilot specific functions
- **Blue Keys**: General VS Code shortcuts
- **Green**: Key pressed state
- **White**: Text and borders
- **Black**: Background