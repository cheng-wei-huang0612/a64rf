# 🚀 **A64RF: ARMv8-A Register Playground**

**A64RF** is a minimal and experimental framework for quickly emulating ARM64 instructions and inspecting CPU register state snapshots. Designed for developers and researchers interested in low-level ARMv8-A assembly programming, debugging, and performance analysis.

---

## ✨ Key Features

* **Lightweight Snapshotting**: Efficiently capture and inspect general-purpose and NEON vector register states.
* **Instruction Emulation**: Basic support for ARMv8-A instruction emulation with an easy-to-use API.
* **Assembly Integration**: Simple macros provided for convenient integration within assembly code.
* **Portability**: Entirely written in pure C, ensuring easy integration and portability across various platforms.

---

## 📌 Quick Start

Clone the repository and run examples:

```bash
git clone https://github.com/yourname/a64rf.git
cd a64rf/tests
gcc -I../include example000.c -o example000
./example000
```

Sample Output:

```
=== GPR value (hex / dec / oct) ===
X0 = 0xf23456789abcdef0
X0 = -994074541749903632
X0 = 0o1710642547423257157360

=== Vector register interpret as {2D,4S,8H,16B} ===
V0: d[0] = 0xaa55aa55aa55aa55, d[1] = 0x55aa55aa55aa55aa
V0: s[0] = 0xaa55aa55, s[1] = 0xaa55aa55, s[2] = 0x55aa55aa, s[3] = 0x55aa55aa
V0: h[0]=0xaa55, h[1]=0xaa55, h[2]=0xaa55, h[3]=0xaa55, h[4]=0x55aa, h[5]=0x55aa, h[6]=0x55aa, h[7]=0x55aa
V0: b[0]=0x55, b[1]=0xaa, b[2]=0x55, b[3]=0xaa, b[4]=0x55, b[5]=0xaa, b[6]=0x55, b[7]=0xaa, b[8]=0xaa, b[9]=0x55, b[10]=0xaa, b[11]=0x55, b[12]=0xaa, b[13]=0x55, b[14]=0xaa, b[15]=0x55

=== ADDS & flag demo ===
X0 = 0xf23456789abcdef0
X1 = 0xffedcba987654321
NZCV = N:0 Z:0 C:0 V:0

=== PERFORM ADDS X2, X0, X1 ===
X2 = 0xf222222222222211
NZCV = N:1 Z:0 C:1 V:0

=== PERFORM SUBS XZR, X2, X2 ===
NZCV = N:0 Z:1 C:1 V:0
```

> ⚠️ **Note:** Automated testing is not yet fully implemented; current testing relies on manual verification.

---

## 🗂️ Project Structure

```
a64rf/
├── include/    # Public API headers
├── src/        # Core snapshot and emulation implementations
├── tests/      # Example programs for manual testing
└── asm.S       # Demonstration of assembly macro usage
```

---

## 🚧 Current Status and Roadmap

The project is currently experimental:

* ✅ Snapshot and register dump functionalities are stable.
* 🚧 Instruction emulation features are partially complete and under active development.
* 🚧 Automated testing infrastructure (potentially involving QEMU integration) is planned but not yet implemented.

---

## 🤝 How to Contribute

Formal contribution guidelines are not yet available, but your help is highly appreciated:

* Report bugs or suggest improvements via GitHub Issues.
* Submit Pull Requests for enhancements or fixes.
* Reach out if you have experience with automated testing or QEMU integration.

---

## 📄 Licensing

A license for this project has not yet been determined. If you have recommendations or preferences, please get in touch!

---

Feel free to explore, test, and provide feedback—your insights will greatly enhance this project's growth!
