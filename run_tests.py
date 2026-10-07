"""Discover per-algorithm tests and optionally compile/run their C++ regressions."""

import argparse
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--cpp",
        action="store_true",
        help="also run C++ regression tests (requires g++)",
    )
    arguments = parser.parse_args()
    suite = unittest.defaultTestLoader.discover(str(ROOT), pattern="test_*.py")
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    if not result.wasSuccessful():
        return 1
    if not arguments.cpp:
        return 0
    compiler = shutil.which("g++")
    if compiler is None:
        parser.error("--cpp requires g++ on PATH")
    with tempfile.TemporaryDirectory(prefix="algorithms-tests-") as temporary:
        for source in sorted(ROOT.glob("*/*.cpp")):
            if source.name.startswith("test_"):
                continue
            # Snippets without main are compiled independently as objects.
            subprocess.run(
                [
                    compiler,
                    "-std=c++17",
                    "-c",
                    str(source),
                    "-o",
                    str(Path(temporary, source.stem + ".o")),
                ],
                check=True,
            )
        for path in sorted(ROOT.glob("*/test_*.cpp")):
            executable = Path(temporary, path.parent.name)
            subprocess.run(
                [
                    compiler,
                    "-std=c++17",
                    "-O1",
                    "-fsanitize=undefined",
                    "-fno-sanitize-recover=all",
                    str(path),
                    "-o",
                    str(executable),
                ],
                check=True,
            )
            subprocess.run([str(executable)], check=True, timeout=30)
            print(f"C++ passed: {path.parent.name}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
