"""Compiles and runs every materials/**/solution/test.cpp.

    python materials/_check/run_all.py            all
    python materials/_check/run_all.py lw2        only paths containing "lw2"

For each solution folder: test.cpp + every other .cpp in the folder whose name does not
start with main/demo/example (those have their own main and are compiled separately
to make sure they build).
"""
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CHECK = ROOT / "_check"
flt = sys.argv[1] if len(sys.argv) > 1 else ""
tmp = Path(tempfile.gettempdir()) / "cse211-materials"
tmp.mkdir(exist_ok=True)
bad = 0
for test in sorted(ROOT.rglob("solution/test.cpp")):
    d = test.parent
    rel = d.relative_to(ROOT).as_posix()
    if flt not in rel:
        continue
    libs = [p for p in d.glob("*.cpp") if p.name != "test.cpp" and not p.name.startswith(("main", "demo", "example"))]
    exe = tmp / (rel.replace("/", "_") + ".exe")
    cmd = ["g++", "-std=c++17", "-Wall", "-Wextra", "-g", f"-I{CHECK}", f"-I{d}", str(test), *map(str, libs), "-o", str(exe)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0 or r.stderr.strip():
        print(f"COMPILE {rel}\n{r.stderr[:3000]}")
        bad += 1
        continue
    run = subprocess.run([str(exe)], capture_output=True, text=True, timeout=60, cwd=d)
    out = run.stdout.strip().splitlines()
    print(out[-1] if out else f"(no output) {rel}")
    if run.returncode != 0:
        print("\n".join(out[:-1][:20]))
        bad += 1
    for m in sorted(d.glob("*.cpp")):
        if m.name.startswith(("main", "demo")):
            r = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", f"-I{d}", str(m), *map(str, libs),
                                "-o", str(tmp / "m.exe")], capture_output=True, text=True)
            if r.returncode != 0 or r.stderr.strip():
                print(f"COMPILE {rel}/{m.name}\n{r.stderr[:2000]}")
                bad += 1
print("\nall solutions OK" if bad == 0 else f"\n{bad} problem(s)")
sys.exit(1 if bad else 0)
