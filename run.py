import subprocess
import sys

_COMMANDS = {
    "main": "cmake -S . -B build -G Ninja && cmake --build build && ./build/app",
    "test": "cmake -S . -B build -G Ninja && cmake --build build && ctest --test-dir build --output-on-failure",
}


def main() -> int:
    match sys.argv[1:]:
        case [arg, *_] if arg in _COMMANDS:
            command = _COMMANDS[arg]
            subprocess.run(command, shell=True, check=False)
            return 0
        case _:
            print("Options: ")
            print("\n".join(_COMMANDS.keys()))
            return 1


if __name__ == "__main__":
    sys.exit(main())
